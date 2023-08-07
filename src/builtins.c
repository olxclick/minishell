/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/07 17:01:29 by jbranco-         ###   ########.fr       */
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
	else if (ft_strcmp(expr->args[0], "export") == 0)
		do_export(expr, my_envs);
	// else if (ft_strcmp(expr->args[0], "unset") == 0)
	// 	do_unset(expr);
}

void	add_env(char **envs, char *str_to_add)
{
	int	size;

	size = get_envs_size(envs);
	envs = ft_realloc(envs, size + 1);
	envs[size + 1] = ft_strdup(str_to_add);
	envs[size + 2] = NULL;
}

void	do_export(t_args *expr, char **envs)//declare -x (ordem alfabetica) || criar variaveis
{
	if (expr->args[1])
		add_env(envs, expr->args[1]);
	else
		sort_envs(envs);
}

void	envs_printer(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		printf("declare -x ");
		printf("%s\n", envs[i]);
		i++;
	}
}

void	swap(char** a, char** b)
{
	char* temp = *a;
	*a = *b;
	*b = temp;
}

int	get_envs_size(char **envs)
{
	int	i;
	
	i = 0;
	while (envs[i])
		i++;
	return (i);
}

void	sort_envs(char** envs)
{
	int	i;
	int	j;
	int	size;

	
	i = 0;
	j = 0;
	size = get_envs_size(envs);
	while (envs[i])
	{
		while (j < size - i - 1)
		{
			if (strcmp(envs[j], envs[j + 1]) > 0)
				swap(&envs[j], &envs[j + 1]);
			j++;
		}
		i++;
		j = 0;
	}
	envs_printer(envs);
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

void	do_exit(t_args *expr, t_params *params) //checkar exit_status here
{
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
