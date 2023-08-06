/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:22:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/06 15:12:50 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"

void cd_home(t_env **env_list, char **new_dir_path)
{
    char buf[10000];
    char *dir;
    t_env *output;  

    dir = getcwd(buf, sizeof(buf));

    if (!new_dir_path || (*new_dir_path != NULL && (ft_strncmp(*new_dir_path, "--", 3) == 0
		|| ft_strncmp(*new_dir_path, "~",2) == 0)))
    {
        output = searching_key(*env_list, "OLDPWD");
        if (output == NULL)
        {
            _print(2,"minishell: cd: OLDPWD not set\n");
            g_info.exit_status = 1;
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

void cd_3(t_env **env_list, char **new_dir_path)
{
    char buf[10000]; 
    char *pwd;
    
     //("%s\n",new_dir_path[1]);
    /**  i added new_dir_path[1] condition (!) */
    if (*new_dir_path != NULL && new_dir_path[1] && ft_strncmp(new_dir_path[1], "-",2) != 0 &&
        ft_strncmp(new_dir_path[1], "~", 2) != 0 && strncmp(new_dir_path[1], "--", 3) != 0)
    {    
        pwd = getcwd(NULL, 0);
        if (chdir(new_dir_path[1]) != 0)
        {
            perror("1 cd");
            g_info.exit_status = 1;
        }
        else
        {
            *new_dir_path =  getcwd(buf, sizeof(buf));
            set_pwd(env_list, *new_dir_path);
            set_oldpwd(env_list, pwd);
            free(pwd);
        }         
    }
}

void ft_cd(t_env **env_list, char **new_dir_path)
{
    char buf[10000];
    char *dir;
    t_env *output; 

	dir = getcwd(buf, sizeof(buf));
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
    /** i changed new_dir_path with &new_dir_path[1] (!) */
    cd__(env_list, &new_dir_path[1]);
    cd_home(env_list, &new_dir_path[1]);
    /**********************************************/
    cd_3(env_list, new_dir_path);
    //g_info.exit_status = 0;            /*(!)*/

}
