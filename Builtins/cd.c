/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:22:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 00:08:49 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"

void cd_3(t_env **env_list, char **new_dir_path);

void cd_home(t_env **env_list, char **new_dir_path)
{
    //char buf[10000];
    char *dir;
    t_env *output;  

	if (*new_dir_path && !ft_strncmp(*new_dir_path, "--", 3) && new_dir_path[1])
    {
        cd_3(env_list, &new_dir_path[1]);
    }
	else if (!new_dir_path || (*new_dir_path != NULL && (ft_strncmp(*new_dir_path, "--", 3) == 0
		|| ft_strncmp(*new_dir_path, "~",2) == 0)))
    {
        dir = getcwd(NULL, 0);
        output = searching_key(*env_list, "OLDPWD");
        if (output == NULL)
        {
            _print(2,"minishell: cd: OLDPWD not set\n");
            g_info.exit_status = 1;
            free(dir);
        }
        else
        {
            
            output = searching_key(*env_list, "HOME");
            set_pwd(env_list, output->val);
            set_oldpwd(env_list, dir);
            chdir(output->val);
            g_info.exit_status = 0;
        }
    }
}

int  old_erreur(t_env *s)
{
    if (s->val == NULL) 
    {
        _print(2,"minishell: cd: OLDPWD not set\n");
        g_info.exit_status = 1;
    }
    return (1);
}

void cd__(t_env **env_list, char **new_dir_path)
{

    t_env *output;
    char *pwd;
    
    if (*new_dir_path != NULL && (strncmp(*new_dir_path, "-", 2) == 0))
     {
        output = searching_key(*env_list, "OLDPWD");
		if (!output->val)
        {
            old_erreur(output);
            return;
        } 
        pwd = getcwd(NULL, 0);
        if (output->val && chdir(output->val) == 0)
        {
            set_pwd(env_list, output->val); 
            set_oldpwd(env_list, pwd); 
            free(pwd);
            output = searching_key(*env_list, "PWD");
            printf("~%s\n", output->val);
        }
        else
        {
            perror("cd");
            g_info.exit_status = 1;
        }
    }
}

void cd_3(t_env **env_list, char **cmds)
{
    //char buf[10000]; 
    char *dir_path;
    char *pwd;
    
 if (*cmds != NULL && ft_strncmp(*cmds, "-",2) != 0 &&
        ft_strncmp(*cmds, "~", 2) != 0 && strncmp(*cmds, "--", 3) != 0)
    {    
        pwd = getcwd(NULL, 0);
        if (chdir(*cmds) != 0)
        {
            _print(2, "minishell: cd: %s: ", *cmds);
			perror(NULL);
            g_info.exit_status = 1;
        }
        else
        {
            dir_path =  getcwd(NULL, 0);
            set_pwd(env_list, dir_path);
            set_oldpwd(env_list, pwd);
            free(dir_path);
        }
        free(pwd);
    }
}

void ft_cd(t_env **env_list, char **new_dir_path)
{
    //char buf[10000];
    char *dir;
    t_env *output; 

	dir = getcwd(NULL, 0);
	if (ft_strcmp(*new_dir_path, "cd") == 0 && !(new_dir_path[1]))
    {
        output = searching_key(*env_list, "HOME");
		if (output == NULL)
        {
            _print(2,"minishell: cd: HOME not set\n");
            g_info.exit_status = 1;
        }
        else if (output != NULL && dir != NULL)
        {
            set_pwd(env_list, output->val);
            chdir(output->val);
            set_oldpwd(env_list, dir);
        }
    }
    free(dir);
    /** i changed new_dir_path with &new_dir_path[1] (!) */
    cd__(env_list, &new_dir_path[1]);
    cd_home(env_list, &new_dir_path[1]);
    /**********************************************/
    cd_3(env_list, &new_dir_path[1]);
    //g_info.exit_status = 0;            /*(!)*/

}
