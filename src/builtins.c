/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/01 17:49:52 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "exit") == 0) || (ft_strcmp(cmd, "pwd") == 0) || (ft_strcmp(cmd, "cd") == 0)
        || (ft_strcmp(cmd, "echo") == 0) || (ft_strcmp(cmd, "export") == 0 || (ft_strcmp(cmd, "unset") == 0));
}

void	do_pwd()
{
	char	cwd[PATH_MAX];

	printf("%s\n", getcwd(cwd, PATH_MAX));
}

void	exec_child_builtin(t_args *expr, t_params *params)
{
	(void)params;
	if (ft_strcmp(expr->args[0], "echo") == 0)
		do_echo(expr);
	else if (ft_strcmp(expr->args[0], "pwd") == 0)
		do_pwd(expr);
}

void	exec_parent_builtin(t_args *expr, t_params *params, char **my_envs)
{
	if (ft_strcmp(expr->args[0], "exit") == 0)
		do_exit(expr, params);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		do_env(my_envs);
	// else if (ft_strcmp(expr->args[0], "export") == 0) declare -x (ordem alfabetica) || criar variaveis
	// 	do_export(expr);
	// else if (ft_strcmp(expr->args[0], "unset") == 0)
	// 	do_unset(expr);
}

void	do_env(char **my_envs)
{
	int	i;

	i = 0;
	while (my_envs[i])
		printf("%s\n", my_envs[i++]);
}

void	do_echo(t_args *expr)
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = (ft_strcmp(expr->args[1], "-n") == 0) ? 2 : 1;
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
	(ft_strcmp(expr->args[1], "-n") != 0) ? printf("\n") : 0;
}

void	do_exit(t_args *expr, t_params *params)
{
	printf("\n exit");
	printf("exit\n");
	if (expr->len >= 3)
		printf("too many arguments\n");
	else if (expr->len == 2)
	{
		params->exit_status = ft_atoi(expr->args[1]) % 256;
		params->exited = 1;
	}
	else
		params->exited = 1;
}
