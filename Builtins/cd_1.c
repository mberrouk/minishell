/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:52:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 01:26:49 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	old_erreur(t_env *s, int flag)
{
	if (flag == 1)
	{
		perror("cd");
		g_info.exit_status = 1;
	}
	else if (s->val == NULL)
	{
		_print(2, "minishell: cd: OLDPWD not set\n");
		g_info.exit_status = 1;
	}
	return (1);
}

void	cd__(t_env **env_list, char **new_dir_path)
{
	t_env	*output;
	char	*pwd;

	if (*new_dir_path != NULL && (ft_strncmp(*new_dir_path, "-", 2) == 0))
	{
		output = searching_key(*env_list, "OLDPWD");
		if (!output->val)
		{
			old_erreur(output, 0);
			return ;
		}
		pwd = getcwd(NULL, 0);
		if (output->val && chdir(output->val) == 0)
		{
			set_pwd(env_list, output->val);
			set_oldpwd(env_list, pwd);
			free(pwd);
			output = searching_key(*env_list, "PWD");
			printf("~%s\n", output->val);
		}
		else
			old_erreur(NULL, 1);
	}
}
