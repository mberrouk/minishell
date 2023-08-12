/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:25 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 05:45:31 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <errno.h>
# include <sys/fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "minishell.h"

/**
 * utils_strings.c
 */

int		ft_strlen(char *str);
int		skip_withespace(char *cmd, int i);
char	*ft_realloc(char *str, char c);
int		ft_strlcpy(char *dest, char *src, int dstsize);
char	*ft_strjoin(char *s1, char *s2);

/**
 * lexer.c
 */
int		tokenize_symbol(char *line, t_lexer *ptr);
void	lexical_analysis(char *line, t_lexer **lst);

/**
 * parser.c
 */
void	init_parse(t_cmd **cmd, char *line, char *env[]);
void	add_file(t_file **file_area, t_file *file);
t_file	*new_file(t_SymTok	type, char *name, int cases);

/**
 * exec_test.c
 */
void	exec_cmds(t_cmd *data, int status, char **env);

/**
 * linked_list.c
 */
void	lexer_lstadd_back(t_lexer **lst, t_lexer *node);
t_lexer	*lexer_lstnew(void *content);
void	parser_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*parser_lstnew(void *content);

/**
 * ft_split.c
 */
char	**ft_split(char const *s, char c);

/**
 * err_utils.c
 */
void	*print_err(char *str);
char	**free_double(char **s);

/**
 * utils_strings1.c
 */
int		check_quots(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);

/**
 * utils_double_ptr.c
 */
char	**join_double(char **fir, char *last);
int		double_len(char **ptr);

/**
 * expansion_utils.c
 */
int		sp_stay(char ch);
int		check_sp_char(char c);
int		sp_remove(char ch);
int		sp_at_end(char ch);
int		handl_spchar_cases(char *arg, char **value);

/**
 * expansion_analsis.c
 */
char	*expan_arg(char *arg, char *env[]);
char	*continue_pars(char **env, char *arg, int *i, char sep);
char	*pars_arg_expan(char *arg, char **env);

/**
 * expansion_in_doublq.c
 */
int		not_expand(char **value, char *arg);
int		expand_it(char **value, char *arg, char **env);
int		handl_cases(char **value, char *arg, int ndol);
char	*expan_in_dquots(char *arg, char **env);

/**
 * parsing_utils.c
 */
void	hold_args2(t_lexer *ptr, t_cmd *tmp, char **ttmp, int drp);
char	**add_simple_cmd(char **ttmp, t_lexer *ptr, t_cmd *tmp);
int		len_to_spchar(char *arg);
int		skip_char(char *str, char c);
int		len_at_char(char *str, char c);
char	*get_var(char *var, char **env);

/**
 *  expansion_utils2.c
 */
int		skip_dollar(char **value, char *arg);
int		check_after_skip(char **value, char *arg, char sep, int *i);
int		check_sep(char arg, char sep);
char	*quots_expan(char **env, char *arg, char sep, int *i);
int		_strncmp(char *s1, char *s2, int n);

/**
 */
char	*ft_itoa(int n);

/**
 * env_process.c
 */
t_env	*new_node(char *key, char *val, int idx);
void	add_node(t_env **lst, t_env *new);
void	fetch_env(t_env **envlist, char **env);
void	printf_env(t_env *list_env);
int		getenv_size(void);

/**
 * ft_printf.c
 */
void	_print(int fd, char *str, ...);

/**
 * clean_utils.c
 */
void	clean_file(t_file *file);
void	clean_parss(t_cmd **cmd);
void	clean_lexer(t_lexer *data);
int		skip_dollar(char **value, char *arg);
char	**ultra_split(char *str, char *charset);

/**
 * herdoc_utils.c
 */
void	count_herdoc(t_file *file);
void	wait_child(pid_t pid, t_cmd *data, int *tab);

/**
 * main_sign.c
 */
void	signals(void);
void	sigint(int sig);

/**
 * exec_utils.c
 */
void	chois_exit_s(char *arg);

#endif
