/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:14 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/25 14:34:53 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(t_envs *envs, char *buffer)
{
	int	pwd_pos;
	int	oldpwd_pos;

	pwd_pos = pos_env_var(envs, "PWD");
	oldpwd_pos = pos_env_var(envs, "OLDPWD");
	if (envs->oldpwd)
		free(envs->oldpwd);
	if (!buffer)
		envs->oldpwd = getcwd(envs->buf, PATH_MAX);
	else
		envs->oldpwd = ft_strdup(buffer);
	free(envs->vars[oldpwd_pos]);
	free(envs->vars[pwd_pos]);
	envs->vars[pwd_pos] = ft_strjoin("PWD=", envs->oldpwd);
	envs->vars[oldpwd_pos] = ft_strjoin("OLDPWD=", envs->pwd);
}

char	*get_home(t_envs *my_envs, char *value)
{
	int	dir;
	int	start;

	dir = 0;
	dir = pos_env_var(my_envs, "HOME");
	start = get_lenght(my_envs, dir);
	value = ft_substr(my_envs->vars[dir], start, ft_strlen(my_envs->vars[dir]));
	return (value);
}

char	*check_cd(t_args *expr, char *value)
{
	struct stat	buf;

	if (stat(expr->args[1], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			value = ft_strdup(expr->args[1]);
		else
		{
			printf("cd: path is not a directory\n");
			g_exit = 1;
		}
	}
	else
	{
		printf("cd: unable to access path\n");
		g_exit = 1;
	}
	return (value);
}

char	*change_dir(t_list *expressions, t_args *expr, t_envs *my_envs, char *value)
{
	if (check_for_pipe(expressions))
		return (NULL);
	if (expr->len == 1 || (!ft_strcmp(expr->args[1], "~")
			&& expr->len == 2))
		value = get_home(my_envs, value);
	else if (!ft_strcmp(expr->args[1], "-") && expr->len == 2)
		value = ft_strdup(my_envs->oldpwd);
	else if (expr->args[1] && expr->len == 2)
		value = check_cd(expr, value);
	return (value);
}

int	dir_change(t_list *expressions, t_args *expr, t_envs *my_envs)
{
	char	*value;

	value = NULL;
	my_envs->buf = NULL;
	if (expr->len > 2)
	{
		printf("cd: invalid number of arguments\n");
		g_exit = 2;
	}
	else
		value = change_dir(expressions, expr, my_envs, value);
	if (chdir(value) == 0)
		update_pwd(my_envs, NULL);
	// else
	// 	update_pwd(my_envs, NULL);
	cd_free(value, my_envs);
	return (g_exit);
}
