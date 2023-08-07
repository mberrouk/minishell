/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:42:34 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/07 01:52:25 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "include/shell.h"
void	builtins_main(t_env **env_list, t_cmd *cmds);
int	builtin_status(char **str);

void	not_found(char *parm)
{
	write(STDERR_FILENO, "minishell: ", 12);
	if (parm && *parm)
		write(STDERR_FILENO, parm, ft_strlen(parm));
	write(STDERR_FILENO, ": command not found\n", 21);
	free(parm);
	exit(127);
}

void	puterr(char *str)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		exit(errno);
	}
	else
	{
		perror("Error");
		exit(errno);
	}
}

char	*ft_access(char **paths, char *cmd)
{
	char	*new;
	char	*v_cmd;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!new)
		return (NULL);
	new[0] = '/';
	ft_strlcpy(&new[1], cmd, ft_strlen(cmd) + 1);
	while (paths && paths[i])
	{
		v_cmd = ft_strjoin(paths[i], ft_strdup(new));
		if (!access(v_cmd, X_OK))
		{
			free(new);
			return (v_cmd);
		}
		free(v_cmd);
		i++;
	}
	free(new);
	return (NULL);
}

char	**find_path(char **env)
{
	char	**paths;
	int		i;
	int		j;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (!path[j])
		{
			paths = ft_split(&env[i][j], ':');
			return (paths);
		}		
		i++;
	}
	return (NULL);
}

void	execute_command(int ifd, int *pip, t_cmd *data, char **cmds, char **path, char **env)
{
	pid_t	pid;
	char	*cmd;
	(void)data;

	pid = fork();
	if (pid == 0)
	{
		if (ifd > 0)
			if (dup2(ifd, STDIN_FILENO) == -1 )
				puterr("1 :Error dup2\n");
		if (ifd == -1)
			return ;
		if (pip[1] > 1)
		{
			if (dup2(pip[1], STDOUT_FILENO) == -1)
				puterr("2 :Error dup2\n");
			if (pip[1] == -1)      							 /** for the failure of dup2 **/
			{
				close(ifd);
				return ;
			}
		}
		if (pip[1] > 1) 										/** close all fd files**/
			close(pip[1]);
		if (ifd > 0)
			close(ifd);
	 	if (pip[0] > 0)
			close(pip[0]);
		if (builtin_status(data->cmd) != -1)					/** check for builtin **/
		{
			builtins_main(&g_info.g_env, data);
			exit(0);
		}
		else
		{
			if (cmds && cmds[0] && (cmds[0][0] == '/' || cmds[0][0] == '.'))
				cmd = cmds[0];
			else
				cmd = ft_access(path, cmds[0]);
			if (!cmd)
			{
				not_found(cmds[0]);
				exit(127);
			}
			if (execve(cmd, cmds, env) == -1)
			{
				puterr(NULL);
				exit(errno);
			}
		}
	}
	else if (pid < 0)
		puterr(NULL);
}

void	open_fd_file(t_cmd *data, int *fdi, int *fdo, int *fdapp)
{
	while (data->file)
	{
		if (data->file->type == INPUT_RE)
		{
			if (*fdi != 0)
				close(*fdi);
			*fdi = open(data->file->name, O_RDONLY);
			if (*fdi == -1)
				perror(data->file->name);
		}
		else if (data->file->type == OUTPUT_RE)
		{
			data->type = data->file->type;
			if (*fdo != 1)
				close(*fdo);
			*fdo = open(data->file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fdo == -1)
				perror(data->file->name);
		}
		else if (data->file->type == APPEND_RE)
		{
			data->type = data->file->type;
			if (*fdapp != -1)
				close(*fdapp);
			*fdapp = open(data->file->name, O_APPEND | O_CREAT | O_RDWR);
			if (*fdapp == -1)
				perror(data->file->name);
		}
		//else if (data->file->type == HERE_DOC)
		//	*fdi = data->file->fd;
		data->file = data->file->next;
	}
}

void	cmds(t_cmd *data, int fdi, char **path, char **env)
{
	int	pip_fds[2];
	int	fdo;
	int	fdapp = -1;

	pip_fds[1] = 1; 
	pip_fds[0] = 0; 
	while (data)
	{
		fdo = 1;
		if (!data->cmd && !data->file)
			return ;
		open_fd_file(data, &fdi, &fdo, &fdapp);
		if (data->type == APPEND_RE)
		{
			if (fdo != 1)
				close(fdo);
			fdo = fdapp;
		}
		if (data->next)
		{	
			if (pipe(pip_fds) == -1)
				puterr(NULL);
			if (fdo > 1)
			{
				close(pip_fds[1]);
				pip_fds[1] = fdo;
			}
		}
		else
		{
			pip_fds[1] = fdo;
		}
		execute_command(fdi, pip_fds, data, data->cmd, path, env);
		if (fdi != 0)
			close(fdi);
		if (pip_fds[1] != 1)
			close(pip_fds[1]);
		fdi = pip_fds[0];
		data = data->next;
	}
	if (fdi != 0)
		close(fdi);
}

int	ft_lstsize_s(char **lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst[i])
	{
		i++;
	}
	return (i);
}

int	builtin_status(char **str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp("cd", str[0], 3))
		return (1);
	if (!ft_strncmp("pwd", str[0], 4))
		return (0);
	if (!ft_strncmp("echo", str[0], 5))
		return (0);
	if (!ft_strncmp("exit", str[0], 5))
		return (1);
	if (!ft_strncmp("env", str[0], 4))
		return (0);
	if (!ft_strncmp("unset", str[0], 6))
		return (1);
	if (!ft_strncmp("export", str[0], 7))
	{
		if (!str[1])
			return (0);
		return (1);
	}
	return (-1);
}

int size_cmds(t_cmd *cmds);

void	exec_cmds(t_cmd *data, int status, char **env)
{
	char **path;
	
	if (!data)
		return ;
	//data->env = env;
	//(ft_lstsize_s(data->cmd) == 1 && (builtin_status(data->cmd) != -1)  (!)
	if (builtin_status(data->cmd) != -1 && (size_cmds(data) == 1))	
		builtins_main(&g_info.g_env, data);
	else
	{
		path = find_path(env);
		cmds(data, 0, path, env);
		while (wait(&status) > 0)
			;
		status = WEXITSTATUS(status);
		free_double(path);
	}
}