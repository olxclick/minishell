/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:32:41 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/10 12:08:47 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_envs(char **envs)
{
	char	**my_envs;
	int	i;

	i = 0;
	my_envs = malloc((get_envs_size(envs) + 1) * sizeof(char *));
	while (envs[i])
	{
		my_envs[i] = ft_strdup(envs[i]);
		i++;
	}
	my_envs[i] = NULL;
	return (my_envs);
}

void	sort_envs(char	**envs)
{
	char	**envs_copy;
	int	i;
	int	j;

	i = 0;
	envs_copy = set_envs(envs);
	while (envs_copy[i])
	{
		j = 0;
		while (j < get_envs_size(envs_copy) - i - 1)
		{
			if (strcmp(envs_copy[j], envs_copy[j + 1]) > 0)
				swap(&envs_copy[j], &envs_copy[j + 1]);
			j++;
		}
		i++;
	}
	envs_printer(envs_copy);
	free_envs(envs_copy);
}
