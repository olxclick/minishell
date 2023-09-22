/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:14 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/22 17:36:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
void	update_pwd(t_envs *envs, char *buffer)
{
	if (envs->oldpwd)
		free(envs->oldpwd);
	if (!buffer)
		envs->oldpwd = getcwd(envs->buf, PATH_MAX);
	else
		envs->oldpwd = ft_strdup(buffer);
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
	struct stat buf;

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

char	*change_dir(t_args *expr, t_envs *my_envs, char *value)
{
	if (!ft_strcmp(expr->args[1], "-") && expr->len == 2)
		value = ft_strdup(my_envs->oldpwd);
	else if (expr->args[1] && expr->len == 2)
		value = check_cd(expr, value);
	return (value);
}
int	dir_change(t_args *expr, t_envs *my_envs)
{
	char	*value;
	char	*buffer;

	value = NULL;
	buffer = NULL;
	my_envs->buf = NULL;
	if (my_envs->oldpwd)
		buffer = ft_strdup(my_envs->oldpwd);
	if (expr->len > 2)
	{
		printf("cd: invalid number of arguments\n");
		g_exit = 2;
	}
	else if (expr->len == 1 || (!ft_strcmp(expr->args[1], "~") && expr->len == 2))
		value = get_home(my_envs, value);
	else if (expr->len == 2)
		value = change_dir(expr, my_envs, value);
	if (value)
		update_pwd(my_envs, NULL);
	if (chdir(value) != 0)
		update_pwd(my_envs, buffer);
	cd_free(value, buffer, my_envs);
	return (g_exit);
}
