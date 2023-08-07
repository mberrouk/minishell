/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/07 12:18:15 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "include/shell.h"
void	builtins_main(t_env **env_list, t_cmd *cmds);
int	builtin_status(char **str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp("cd", str[0], 3)
        || !ft_strncmp("pwd", str[0], 4)
        || !ft_strncmp("echo", str[0], 5)
        || !ft_strncmp("exit", str[0], 5)
	    || !ft_strncmp("env", str[0], 4)
        || !ft_strncmp("unset", str[0], 6)
        || !ft_strncmp("export", str[0], 7))
            return (0);
	return (-1);
}

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
		//exit(errno);
		exit(g_info.exit_status);
	}
	else
	{
		perror("Error");
		//exit(errno);
		exit(g_info.exit_status);
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

void handle_builtin_commands(t_cmd *data, char **cmds, char **path, char **env)
{
    char *cmd;
    if (builtin_status(data->cmd) != -1)
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
            exit(g_info.exit_status);
        }
    }
}

void setup_pipes(int ifd, int *pip)
 {
    if (ifd > 0) 
    {
        if (dup2(ifd, STDIN_FILENO) == -1)
            puterr("1: Error dup2\n");
    }
    if (ifd == -1)
        return;
    if (pip[1] > 1)
    {
        if (dup2(pip[1], STDOUT_FILENO) == -1)
        {
            puterr("2: Error dup2\n");
            if (pip[1] == -1)
                close(ifd);
        }
    }
    if (pip[1] > 1)
        close(pip[1]);
    if (ifd > 0)
        close(ifd);
    if (pip[0] > 0) 
        close(pip[0]);
}

void execute_child(int ifd, int *pip, t_cmd *data, char **cmds, char **path, char **env)
 {
    setup_pipes(ifd, pip);
    handle_builtin_commands(data, cmds, path, env);
}

void execute_command(int ifd, int *pip, t_cmd *data, char **cmds, char **path, char **env) 
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0)
        execute_child(ifd, pip, data, cmds, path, env);
    else if (pid < 0) 
        puterr(NULL);
}

void handle_input_redirection(t_cmd *data, int *fd_inp) 
{
    if (data->file->type == INPUT_RE)
    {
        if (*fd_inp != 0)
            close(*fd_inp);
        *fd_inp = open(data->file->name, O_RDONLY);
        if (*fd_inp == -1)
        {
            perror(data->file->name);
            g_info.exit_status = 1;
        }
    }
}

void handle_output_redirection(t_cmd *data, int *fd_oup)
{
    if (data->file->type == OUTPUT_RE)
	{
		data->type = data->file->type;
		if (*fd_oup != 1)
			close(*fd_oup);
		*fd_oup = open(data->file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_oup == -1)
		{
			_print(2, "minishell: ");
			perror(data->file->name);
			g_info.exit_status = 1;
		}
	}
}

void handle_append_redirection(t_cmd *data, int *fd_app)
{
    if (data->file->type == APPEND_RE)
	{
		data->type = data->file->type;
		if (*fd_app != -1)
			close(*fd_app);
		*fd_app = open(data->file->name, O_APPEND | O_CREAT | O_RDWR);
		if (*fd_app == -1)
		{
			_print(2, "minishell: ");
			perror(data->file->name);
			g_info.exit_status = 1;
		}
	}
}

void open_fd_file(t_cmd *data, int *fd_inp, int *fd_oup, int *fd_app)
{
    while (data->file)
    {
        handle_input_redirection(data, fd_inp);
        handle_output_redirection(data, fd_oup);
        handle_append_redirection(data, fd_app);
        data->file = data->file->next;
    }
}

void setup_pipe_fds(int *pip_fds, int fd_oup, int fd_app, int *fd_inp, t_cmd *data, char **path, char **env)
{
    pip_fds[1] = 1; 
    pip_fds[0] = 0;

    if (data->type == APPEND_RE)
    {
        if (fd_oup != 1)
            close(fd_oup);
        fd_oup = fd_app;
    }

    if (data->next)
    {
        if (pipe(pip_fds) == -1)
            puterr(NULL);
        if (fd_oup > 1)
        {
            close(pip_fds[1]);
            pip_fds[1] = fd_oup;
        }
    }
    else
        pip_fds[1] = fd_oup;
    execute_command(*fd_inp, pip_fds, data, data->cmd, path, env);
    if (*fd_inp != 0) 
        close(*fd_inp);
    if (pip_fds[1] != 1)
        close(pip_fds[1]);
}

void execute_commands(t_cmd *data, int fd_inp, char **path, char **env)
{
    int pip_fds[2];
    int fd_oup;
    int fd_app = -1;

    while (data != NULL)
    {
        fd_oup = 1;
        if (!data->cmd && !data->file)
            return;
        open_fd_file(data, &fd_inp, &fd_oup, &fd_app);
        setup_pipe_fds(pip_fds, fd_oup, fd_app, &fd_inp, data, path , env);
        fd_inp = pip_fds[0];
        data = data->next;
    }
    if (fd_inp != 0)
        close(fd_inp);
}

void cmds(t_cmd *data, int fd_inp, char **path, char **env)
{
    execute_commands(data, fd_inp, path, env);
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

int size_cmds(t_cmd *cmds)
{
    int i;
    
    i = 0;
	while(cmds)
	{
		i++;
		cmds = cmds->next;
	}
    return (i);
}

void	exec_cmds(t_cmd *data, int status, char **env)
{
	char **path;
	
	if (!data)
		return ;
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
