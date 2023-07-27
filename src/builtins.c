/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 18:55:46 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_args *expr)
{
	size_t	i;

	i = 0;
	while (i < expr->len)
	{
		if (ft_strcmp(expr->args[i], "exit") == 0)
			return (do_exit(expr));
		else if (ft_strcmp(expr->args[i], "echo") == 0)
			return (do_echo(expr));
		// if (ft_strcmp(args->args[i], "cd") == 0)
		// 	do_cd(args);
		// if (ft_strcmp(args->args[i], "export") == 0)
		// 	do_export(args);
		// if (ft_strcmp(args->args[i], "unset") == 0)
		// 	do_unset(args);
		i++;
	}
	return (0);
}

int	do_echo(t_args *expr)
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = 1;
	while (expr->args[i])
	{
		if (flag)
			printf(" ");
		printf("%s", expr->args[i++]);
		if (expr->args[i])
			flag = 1;
		else
			flag = 0;
	}
	printf("\n");
	return (1);
}

int	do_exit(t_args *expr)
{
	expr->exited = 1;
	rl_clear_history();
	exit(1);
}