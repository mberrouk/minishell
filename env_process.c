#include "./include/shell.h"

/**
 * new_node - Creates a new node for the environment list
 * @key: The key for the environment variable
 * @val: The value for the environment variable
 * @idx: The index of the environment variable
 *
 * Return: A pointer to the newly created node, or NULL on failure
 */
t_env	*new_node(char *key, char *val, int idx)
{
	t_env	*new;

	(void)idx;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0x00);
	new->next = 0x00;
	new->key = key;
	new->val = val;
	return (new);
}

/**
 * add_node - Adds a node to the end of the environment list
 * @lst: A pointer to the head of the environment list
 * @new: A pointer to the node to be added
 */
void	add_node(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/**
 * fetch_env - Fetches the environment variables and creates a linked list
 * @envlist: A pointer to the head of the list
 * @env: The array of environment variables
 */
void	fetch_env(t_env **envlist, char **env)
{
	int		i;
	char	**arg;
	t_env	*tmp;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		arg = ft_split(env[i], '=');
		if (arg)
			add_node(envlist, new_node(ft_strdup(arg[0]), ft_strdup(arg[1]), i));
		free_double(arg);
		i++;
	}
	tmp = *envlist;
	/**  check PWD and remove value in the the first time running program */
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			if (tmp->val)
				free(tmp->val);
			tmp->val = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	/**   add OLDPWD variable on environment if not exists **/
	if (!tmp)
		add_node(envlist, new_node(ft_strdup("OLDPWD"), NULL, i));
}

int getenv_size()
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = g_info.g_env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);	
}
