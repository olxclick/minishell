/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:14 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/21 17:27:51 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// void last_pwd(char *dir, t_envs *envs)
// {
//  int     cur;
//  char    *envs_name;
//  t_envs  *head;
//  head = envs;
//  while (envs)
//  {
//      cur = search_sub_for_ocurr(envs->str, "=");
//      envs_name = ft_substr(envs->str, 0, cur);
//      if (!ft_strcmp(envs_name, "OLDPWD"))
//      {
//          if (envs->was_added)
//              free(envs->str);
//          envs->str = form_variable(envs_name, dir);
//          envs->was_added = 1;
//          break ;
//      }
//      free(envs_name);
//      envs = envs->next;
//  }
//  envs = head;
// }
// static void update_pwd(char *oldpwd, t_envs * envs)
// {
//     char    value[PATH_MAX];
//     char    *pwd;
//     int     pos;
//     char    *env_name;
//     pos = search_sub_for_ocurr(envs->str, "=");
//     env_name = ft_substr(envs->str, 0 , pos);
//     pwd = ft_strdup(getcwd(value, PATH_MAX));
//     while(envs)
//     {
//         if (!ft_strcmp(env_name, "PWD"))
//         {
//             if (envs->was_added)
//                 free(envs->str);
//             envs->str = form_variable(env_name, pwd);
//             envs->was_added = 1;
//             break;
//         }
//         free(env_name);
//         envs = envs->next;
//     }
//     last_pwd(oldpwd, envs);
//     free(pwd);
// }

int	get_lenght(t_envs *envs, int i)
{
	int	j;

	j = 0;
	while(envs->vars[i][j])
	{
		if (envs->vars[i][j] == '=')
			return (j + 1);
		j++;
	}
	return (j);
}

int	dir_change(t_args *expr, t_envs *my_envs)
{
	char *value;
	int dir;
	int start;

	dir = 0;
	value = NULL;
	my_envs->buf = NULL;
	my_envs->oldpwd = getcwd(my_envs->buf, PATH_MAX);
	if ((!ft_strcmp(expr->args[1], "~") && expr->len == 2) || expr->len == 1)
	{
		dir = pos_env_var(my_envs, "HOME");
		start = get_lenght(my_envs, dir);
		value = ft_substr(my_envs->vars[dir], start, ft_strlen(my_envs->vars[dir]));
	}
	else if (!ft_strcmp(expr->args[1], "-") && expr->len == 2)
	{
		printf("oldpwd: %s\n", my_envs->oldpwd);
		chdir(my_envs->oldpwd);
	}
	else if (expr->args[1] && expr->len == 2)
		value = ft_strdup(expr->args[1]);
	if (value && chdir(value) != 0)
	{
		g_exit = 1;
		printf("cd: Unknown Path\n");
	}
	//else
	//{
	//    update_pwd(ft_strdup(oldpwd), my_envs); // Changed the parameter name
	//}
	free(value);
	free(my_envs->buf);
	free(my_envs->oldpwd);
	return (g_exit);
}