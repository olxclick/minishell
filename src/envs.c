/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:32:41 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/31 18:13:03 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char **set_envs(char **envs)
{
	char **my_envs;
	int	i;

	i = 0;
	my_envs = malloc((array_size(envs) + 1) * sizeof(char *));
	while (envs[i])
	{
		my_envs[i] = ft_strdup(envs[i]);
		i++;
	}
	my_envs[i] = NULL;
	return (my_envs);
}