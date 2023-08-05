/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:03:00 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/05 08:36:02 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include "../include/shell.h"


void	pwd(void)
{
	char	puf[100000];

	if (getcwd(puf, sizeof(puf)) == NULL)
	{
		perror("pwd");
		g_info.exit_status = 1;
	}
	else
	{
		printf("%s\n", puf);
		g_info.exit_status = 0;
	}
}
