/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:48:16 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/15 13:15:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_path(char *path)
{
	char	*new_path;
	int		i;

	i = 0;
	while (path[i] != '/')
		i++;
	new_path = ft_substr(path, i, ft_strlen(path));
	free(path);
	return (new_path);
}

char	*define_path(t_envs *envs, char *expr)
{
	char	*full_path;
	char	*bin;
	char	**path_env;
	size_t	i;

	i = 0;
	bin = ft_strjoin("/", expr);
	path_env = ft_split(envs->vars[pos_env_var(envs, "PATH")], ':');
	i = -1;
	while (path_env[++i])
	{
		full_path = ft_strjoin(path_env[i], bin);
		if (full_path[0] != '/')
			full_path = check_path(full_path);
		if (access(full_path, F_OK) == 0)
		{
			free_token(path_env);
			free(bin);
			return (full_path);
		}
		free(full_path);
	}
	free_token(path_env);
	free(bin);
	return (NULL);
}

char	*get_path(char *expr, t_envs *envs)
{
	struct stat	buf;

	if (expr[0] == '/' || ft_strncmp(expr, "./", 2) == 0)
	{
		if (access(expr, F_OK) == 0)
		{
			if (stat(expr, &buf) == 0 && (expr[0] == '/' || expr[0] == '.'))
			{
				if (S_ISREG(buf.st_mode))
					return (expr);
			}
		}
		return (NULL);
	}
	if (pos_env_var(envs, "PATH") != -1)
		return (define_path(envs, expr));
	return (NULL);
}
