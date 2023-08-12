/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:12:32 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 20:32:38 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtins_main(t_env **env_list, t_cmd *cmds)
{
	if (ft_strcmp(cmds->cmd[0], "echo") == 0
		|| ft_strcmp(cmds->cmd[0], "eCho") == 0
		|| ft_strcmp(cmds->cmd[0], "ECHO") == 0
		|| ft_strcmp(cmds->cmd[0], "eChO") == 0)
		ft_echo(cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmds->cmd[0], "env") == 0)
		ft_env(*env_list, cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		ft_exit(cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		ft_unset(env_list, cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		ft_cd(env_list, cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "export") == 0)
		ft_export(cmds->cmd, *env_list);
}
