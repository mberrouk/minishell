/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:38:17 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 23:32:05 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_info.exit_status = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
