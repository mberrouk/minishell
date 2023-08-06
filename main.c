/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:16 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/06 03:42:24 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/shell.h"

#include "./include/minishell.h"



char	**convert_env()
{
	char 	**env;
	t_env	*tmp;
	int		len;
	int		i;

	i = 0;
	len = getenv_size();
	env = malloc(sizeof(char *) * (len + 1));
	if (env == NULL)
		return NULL;
	env[len] = NULL;
	tmp = g_info.g_env;
	while(tmp)
	{
		env[i] = ft_strjoin(ft_realloc(ft_strdup(tmp->key), '=')\
		, ft_strdup(tmp->val));
		tmp = tmp->next;
		i++;
	}
	return (env);
}

int	main(int ac, char *av[], char *env[])
{
	(void)av;
	t_cmd	*cmds;
	char	*line;
	char	**tmpenv;

	if (ac != 1)
		return (1);
	line = NULL;
	cmds = NULL;
	fetch_env(&g_info.g_env, env);
	while (1)
	{
		tmpenv = NULL;
		line = readline("\033[1;34mminishell$  \033[1;0m");;
		if (!line)
			return (errno);
		add_history(line);
		if (line && *line)
		{
			tmpenv = convert_env();
			init_parse(&cmds, line, tmpenv);
			//builtins_main(&g_info.g_env, cmds->cmd);
			exec_cmds(cmds, 0, env);
		}
		free(line);
		free_double(tmpenv);
		clean_parss(&cmds);
	}

	/**
	 * Test 
	for (int i = 0; envlist; i++)
	{
		printf("env : %s\n", env[i]);
		printf("envlst : %s %s\n", envlist->key, envlist->val);
		envlist = envlist->next;
	}
	*/
}
