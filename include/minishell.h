/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:39:10 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/07 12:36:33 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
#include <stdbool.h>
#include "../include/lexer.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	int				index;
	struct s_env		*next;
}	t_env;



typedef struct s_da
{
	t_env			*g_env;
	int				exit_status;
}  t_da;

t_da	g_info;

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdarg.h>


typedef struct s_at
{
	int				i;
	int				sig;
	size_t			r;
}	t_at;

typedef struct s_echo
{
    int i;
    int flag;
    int j;
    int k;
}   t_echo;

// typedef struct s_cd
// {
//     char buf[10000];
//     char *dir;
//     t_env *output;
// } t_cd;

typedef struct s_file
{
    SymTok			type;
	char			*name;
	int				fd;			/** the file descripti*/
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
    SymTok			type;
	char			**cmd; 
	t_file			*file;
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_unset
{
    int i;
    t_env *prev;
    t_env *current;
}   t_unset;

typedef struct s_execu
{
	
}	t_execu;

char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const	char	*str);
void	ft_env(t_env *list_env, char **av);
void	pwd(void);
void	ft_echo(char **av);
void	ft_exit(char **av);
void	ft_env(t_env *list_env, char **av);
void	ft_unset(t_env **env_list, char **av);
//void	builtins_main(t_env **env_list, char **line);
void	ft_cd(t_env **env_list, char **new_dir_path);
void    ft_export(char **av, t_env *env);
void	ft_putstr_fd(char *s, int fd);
char	*fstrdup(char *src);
void	set_pwd(t_env **envlist, char *dir);
void	set_oldpwd(t_env **envlist, char *dir);
t_env	*searching_key(t_env *env_list, char *key);
void    free_env(t_env  *current);
int     expo(char **av, t_env	*env);
int     env_len(t_env *env);
void	builtins_main(t_env **env_list, t_cmd *cmd);
int		ft_lstsize_s(char **lst);
void	execution(t_cmd   *cmds, char **env);
int		builtin_status(char **str);
void	puterr(char *str);
void	not_found(char *parm);
char	**find_path(char **env);

#endif 
