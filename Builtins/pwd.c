/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:03:00 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 20:38:31 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

void	pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		perror("pwd");
		g_info.exit_status = 1;
	}
	else
	{
		printf("%s\n", wd);
		g_info.exit_status = 0;
		free(wd);
	}
}
