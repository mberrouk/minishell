/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:16 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 00:55:16 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/shell.h"
#include "./include/minishell.h"

char	**convert_env(void)
{
	char	**env;
	t_env	*tmp;
	int		len;
	int		i;

	i = 0;
	len = getenv_size();
	env = malloc(sizeof(char *) * (len + 1));
	if (env == NULL)
		return (NULL);
	env[len] = NULL;
	tmp = g_info.g_env;
	while (tmp)
	{
		env[i] = ft_strjoin(ft_realloc(ft_strdup(tmp->key), '=')\
			, ft_strdup(tmp->val));
		tmp = tmp->next;
		i++;
	}
	printf("\n---------------------------------\n");
		for (t_env *var = g_info.g_env; var; var = var->next)
		printf("%s  %s\n", var->key, var->val);
	printf("\n---------------------------------\n");
	return (env);
}

int	env_lenn(t_cmd *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = (env)->next;
	}
	return (len);
}

void	sigint(int sig)
{
	(void)sig;
	g_info.exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
}

int	main(int ac, char *av[], char *env[])
{
	t_cmd	*cmds;
	char	*line;
	char	**tmpenv;

	(void)av;
	if (ac != 1)
		return (1);
	line = NULL;
	cmds = NULL;
	fetch_env(&g_info.g_env, env);
	while (1)
	{
		signals();
		tmpenv = NULL;
		line = readline("\033[1;34mminishell$  \033[1;0m");
		if (!line)
			return (errno);
		add_history(line);
		if (line && *line)
		{
			tmpenv = convert_env();
			init_parse(&cmds, line, tmpenv);
			exec_cmds(cmds, 0, env);
		}
		free(line);
		free_double(tmpenv);
		clean_parss(&cmds);
	}
}
