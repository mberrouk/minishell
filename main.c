/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:16 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 05:27:18 by mberrouk         ###   ########.fr       */
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
		env[i] = ft_strjoin(ft_realloc(ft_strdup(tmp->key), '=') \
			, ft_strdup(tmp->val));
		tmp = tmp->next;
		i++;
	}
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

void	continue_loop(char *line, t_cmd **cmds)
{
	char	**tmpenv;

	tmpenv = NULL;
	add_history(line);
	tmpenv = convert_env();
	init_parse(cmds, line, tmpenv);
	exec_cmds(*cmds, 0, tmpenv);
	free(line);
	free_double(tmpenv);
	clean_parss(cmds);
}

int	main(int ac, char *av[], char *env[])
{
	t_cmd	*cmds;
	char	*line;

	(void)av;
	if (ac != 1)
		return (1);
	line = NULL;
	cmds = NULL;
	fetch_env(&g_info.g_env, env);
	while (1)
	{
		signals();
		line = readline("\033[1;34mminishell$  \033[1;0m");
		if (!line)
			return (g_info.exit_status);
		continue_loop(line, &cmds);
	}
	return (g_info.exit_status);
}
