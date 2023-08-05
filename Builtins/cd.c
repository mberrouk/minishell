/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:22:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/05 08:35:24 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"


void cd_home(t_env **env_list, char *new_dir_path)
{
    t_cd vars; 

    vars.dir = getcwd(vars.buf, sizeof(vars.buf));

    if (new_dir_path != NULL && (ft_strcmp(new_dir_path, "--") == 0 || ft_strcmp(new_dir_path, "~") == 0))
    {
        vars.output = searching_key(*env_list, "OLDPWD");
        if (vars.output == NULL)
        {
            _print(2,"minishell: cd: OLDPWD not set\n");
            g_info.exit_status = 1;
        }
        else
        {
            
            vars.output = searching_key(*env_list, "HOME");
            set_pwd(env_list, vars.output->val);
            set_oldpwd(env_list, vars.dir);
            chdir(vars.output->val);
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

void cd__(t_env **env_list, char *new_dir_path)
{
    t_cd vars;
    char *pwd;
    
    if (new_dir_path != NULL && (strcmp(new_dir_path, "-") == 0))
     {
        vars.output = searching_key(*env_list, "OLDPWD");
        if (!vars.output->val)
        {
            old_erreur(vars.output);
            return;
        } 
        pwd = getcwd(NULL, 0);
        if (chdir(vars.output->val) == 0 && vars.output->val)
        {
            set_pwd(env_list, vars.output->val); 
            set_oldpwd(env_list, pwd); 
            free(pwd);
            vars.output = searching_key(*env_list, "PWD");
            printf("~%s\n", vars.output->val);
        }
        else
        {
            perror("cd");
            g_info.exit_status = 1;
        }
    }
}

void cd_3(t_env **env_list, char *new_dir_path)
{
    t_cd vars;
    char *pwd;
    
    if (new_dir_path != NULL && strcmp(new_dir_path, "-") != 0 &&
        strcmp(new_dir_path, "~") != 0 && strcmp(new_dir_path, "--") != 0)
    {    
        pwd = getcwd(NULL, 0);
        if (chdir(new_dir_path) != 0)
        {
            perror("cd");
            g_info.exit_status = 1;
        }
        else
        {
            new_dir_path =  getcwd(vars.buf, sizeof(vars.buf));
            set_pwd(env_list, new_dir_path);
            set_oldpwd(env_list, pwd);
            free(pwd);
        }         
    }
}

void ft_cd(t_env **env_list, char *new_dir_path)
{
    t_cd vars;

    vars.dir = getcwd(vars.buf, sizeof(vars.buf));
    if (new_dir_path == NULL)
    {
        vars.output = searching_key(*env_list, "HOME");
        if (vars.output == NULL)
        {
            _print(2,"minishell: cd: HOME not set\n");
            g_info.exit_status = 1;
        }
        else if (vars.output != NULL && vars.dir != NULL)
        {
            set_pwd(env_list, vars.output->val);
            chdir(vars.output->val);
            set_oldpwd(env_list, vars.dir);
        }
    }
    cd_home(env_list, new_dir_path);
    cd__(env_list, new_dir_path);
    cd_3(env_list, new_dir_path);
    g_info.exit_status = 0;
}
