/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 16:46:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_args *args)
{
	size_t	i;

	i = 0;
	while (i < args->len)
	{
		if (ft_strcmp(args->args[i], "exit") == 0)
			do_exit(args);
		// if (ft_strcmp(args->args[i], "cd") == 0)
		// 	do_cd(args);
		// if (ft_strcmp(args->args[i], "export") == 0)
		// 	do_export(args);
		// if (ft_strcmp(args->args[i], "unset") == 0)
		// 	do_unset(args);
		// if (ft_strcmp(args->args[i], "echo") == 0)
		// 	do_echo(args);
		i++;
	}
	return (0);
}

void	do_exit(t_args *args)
{
	free_all(args);
	rl_clear_history();
	exit(0);
}