/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:22:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 01:40:48 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

void	_to_home(t_env **env_list, t_env *output, char *dir)
{
	if (output == NULL)
	{
		_print(2, "minishell: cd: OLDPWD not set\n");
		g_info.exit_status = 1;
		free(dir);
	}
	else
	{
		output = searching_key(*env_list, "HOME");
		set_pwd(env_list, output->val);
		set_oldpwd(env_list, dir);
		chdir(output->val);
		g_info.exit_status = 0;
	}
}

void	cd_home(t_env **env_list, char **new_dir_path)
{
	char	*dir;
	t_env	*output;

	if (*new_dir_path && !ft_strncmp(*new_dir_path, "--", 3)
		&& new_dir_path[1])
		cd_3(env_list, &new_dir_path[1]);
	else if (!new_dir_path || (*new_dir_path != NULL
			&& (ft_strncmp(*new_dir_path, "--", 3) == 0
				|| ft_strncmp(*new_dir_path, "~", 2) == 0)))
	{
		dir = getcwd(NULL, 0);
		output = searching_key(*env_list, "OLDPWD");
		_to_home(env_list, output, dir);
	}
}

void	cd_3(t_env **env_list, char **cmds)
{
	char	*dir_path;
	char	*pwd;

	if (*cmds != NULL && ft_strncmp(*cmds, "-", 2) != 0
		&& ft_strncmp(*cmds, "~", 2) != 0
		&& strncmp(*cmds, "--", 3) != 0)
	{
		pwd = getcwd(NULL, 0);
		if (chdir(*cmds) != 0)
		{
			_print(2, "minishell: cd: %s: ", *cmds);
			perror(NULL);
			g_info.exit_status = 1;
		}
		else
		{
			dir_path = getcwd(NULL, 0);
			set_pwd(env_list, dir_path);
			set_oldpwd(env_list, pwd);
			free(dir_path);
		}
		free(pwd);
	}
}

void	ft_cd(t_env **env_list, char **new_dir_path)
{
	char	*dir;
	t_env	*output;

	dir = getcwd(NULL, 0);
	if (!(new_dir_path[1]))
	{
		output = searching_key(*env_list, "HOME");
		if (output == NULL || !output->val)
		{
			_print(2, "minishell: cd: HOME not set\n");
			g_info.exit_status = 1;
		}
		else if (output != NULL && dir != NULL)
		{
			set_pwd(env_list, output->val);
			chdir(output->val);
			set_oldpwd(env_list, dir);
		}
	}
	free(dir);
	cd__(env_list, &new_dir_path[1]);
	cd_home(env_list, &new_dir_path[1]);
	cd_3(env_list, &new_dir_path[1]);
}
