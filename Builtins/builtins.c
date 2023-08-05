/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:12:32 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/05 11:21:59 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	builtins_main(t_env **env_list, char **line)
{
	
	if (ft_strcmp(line[0], "echo") == 0 || ft_strcmp(line[0], "eCho") == 0
		|| ft_strcmp(line[0], "ECHO") == 0 || ft_strcmp(line[0], "eChO") == 0 )
		ft_echo(line);
	else if (ft_strcmp(line[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(line[0], "env") == 0)
		ft_env(*env_list, line);
	else if (ft_strcmp(line[0], "exit") == 0)
		ft_exit(line);
	else if (ft_strcmp(line[0], "unset") == 0)
		ft_unset(env_list, line);
	else if (ft_strcmp(line[0], "cd") == 0)
		ft_cd(env_list, *line);
	else if (ft_strcmp(line[0], "export") == 0)
		ft_export(line, *env_list);
 }
