/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:30:01 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 00:12:45 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_args *args)
{
	size_t	i;

	i = 0;
    while (i < args->len)
        free(args->args[i++]);
    free(args);
	rl_clear_history();
}

void	free_envs(char **my_envs)
{
	int	i;

	i = 0;
	while (my_envs[i])
		free(my_envs[i++]);
	free(my_envs);
}
