/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:14 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/22 15:29:56 by jbranco-         ###   ########.fr       */
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
void	update_pwd(t_envs *envs)
{
	if (envs->oldpwd)
		free(envs->oldpwd);
	envs->oldpwd = getcwd(envs->buf, PATH_MAX);
}

int	dir_change(t_args *expr, t_envs *my_envs)
{
	char	*value;
	char	*buffer;
	int	dir;
	int	start;

	dir = 0;
	value = NULL;
	my_envs->buf = NULL;
	buffer = NULL;
	if (my_envs->oldpwd)
		buffer = ft_strdup(my_envs->oldpwd);
	if (expr->len == 1 || (!ft_strcmp(expr->args[1], "~") && expr->len == 2))
	{
		dir = pos_env_var(my_envs, "HOME");
		start = get_lenght(my_envs, dir);
		value = ft_substr(my_envs->vars[dir], start, ft_strlen(my_envs->vars[dir]));
	}
	else if (!ft_strcmp(expr->args[1], "-") && expr->len == 2)
		value = ft_strdup(my_envs->oldpwd);
	else if (expr->args[1] && expr->len == 2)
		value = ft_strdup(expr->args[1]);
	if (value)
		update_pwd(my_envs);
	if (chdir(value) != 0)
	{
		printf("cd: Unknown Path\n");
		free(my_envs->oldpwd);
		my_envs->oldpwd = ft_strdup(buffer);
		g_exit = 1;
	}
	free(value);
	free(buffer);
	free(my_envs->buf);
	return (g_exit);
}
