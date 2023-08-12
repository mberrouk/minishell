/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:39:10 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 02:59:02 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <limits.h>
# include <string.h>

# include "../include/lexer.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_da
{
	t_env			*g_env;
	int				exit_status;
}	t_da;

t_da	g_info;

typedef struct s_at
{
	int							i;
	int							sig;
	unsigned long long			r;
}	t_at;

typedef struct s_echo
{
	int	i;
	int	flag;
	int	j;
	int	k;
}	t_echo;

typedef struct s_file
{
	t_SymTok		type;
	char			*name;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	t_SymTok		type;
	char			**cmd;
	t_file			*file;
	int				input;
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_unset
{
	int		i;
	t_env	*prev;
	t_env	*current;
}	t_unset;

typedef struct s_exec
{
	int		fd_oup;
	int		fd_app;
	int		fd_inp;
	char	**path;
	char	**env;
}	t_exec;

void	cat_handle_sigint(int sig);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_atoi(const	char	*str);
void	ft_env(t_env *list_env, char **av);
void	pwd(void);
void	ft_echo(char **av);
void	ft_exit(char **av);
void	ft_env(t_env *list_env, char **av);
void	ft_unset(t_env **env_list, char **av);
void	ft_cd(t_env **env_list, char **new_dir_path);
void	ft_export(char **av, t_env *env);
void	ft_putstr_fd(char *s, int fd);
char	*fstrdup(char *src);
void	set_pwd(t_env **envlist, char *dir);
void	set_oldpwd(t_env **envlist, char *dir);
t_env	*searching_key(t_env *env_list, char *key);
void	free_env(t_env *current);
int		expo(char **av, t_env	*env);
int		env_len(t_env *env);
void	builtins_main(t_env **env_list, t_cmd *cmd);
int		ft_lstsize_s(char **lst);
void	execution(t_cmd *cmds, char **env);
int		builtin_status(char **str);
void	puterr(char *str);
void	not_found(char *parm);
char	**find_path(char **env);
int		handle_input_redirection(t_cmd *data, t_file *file, int *fd_inp);
int		handle_output_redirection(t_cmd *data, t_file *file, int *fd_oup);
int		handle_append_redirection(t_cmd *data, t_file *file, int *fd_app);
char	*ft_access(char **paths, char *cmd);
void	han_buil_comnds(t_cmd *data, char **cmds, char **path, char **env);
void	setup_pipes(int ifd, int *pip);
int		open_doc(t_cmd *cmd, char **env);
int		execute_command(t_exec fd, int *pip, t_cmd *data, char **cmds);
int		open_fd_file(t_cmd *data, int *fd_inp, int *fd_oup, int *fd_app);
void	cd_3(t_env **env_list, char **cmds);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*cat_equals(char *str, int *x, int i);
void	export_add(char *key, char *value);
int		len_equal(char *s);
char	*come_max(t_env *env);
int		env_len(t_env *env);
void	sort_export(t_env *env, int indice, int size);
void	print(t_env *env, t_env *tmp, int size);
void	help(t_env *tmp, char *key, char *value, int x);
void	envadd_back(t_env **lst, t_env *new);
t_env	*env_new(char *s1, char *s2);
char	*pars_expan(t_lexer *data, char **env);
int		export_help(char **av, t_env *env, char *value, int i);
t_lexer	*hold_args(t_cmd **head, t_lexer *ptr, t_cmd *tmp, char **env);
int		old_erreur(t_env *s, int flag);
void	cd__(t_env **env_list, char **new_dir_path);
int		chhe(char *av, char *par);
#endif 
