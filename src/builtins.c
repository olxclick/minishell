/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/13 14:26:47 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_pwd(t_args *expr)
{
	char	cwd[PATH_MAX];
	(void)expr;
	printf("%s\n", getcwd(cwd, PATH_MAX));
	return (0);
}
int	exec_child_builtin(t_args *expr, t_envs *my_envs)
{
	if (ft_strcmp(expr->args[0], "echo") == 0)
		g_exit = do_echo(expr);
	else if (ft_strcmp(expr->args[0], "pwd") == 0)
		g_exit = do_pwd(expr);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs);
	return (g_exit);
}
int	exec_parent_builtin(t_list *expressions, t_args *expr, t_params *params, t_envs *my_envs)
{
	if (ft_strcmp(expr->args[0], "exit") == 0)
		g_exit = do_exit(expressions, expr, params);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		g_exit = do_env(my_envs);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "unset") == 0)
		g_exit = do_unset(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "cd") == 0)
		g_exit = dir_change(expr, my_envs);
	return (g_exit);
}
int	remove_var(t_envs *my_envs, int pos)
{
	if (pos == my_envs->len - 1)
		free(my_envs->vars[pos]);
	else
	{
		free(my_envs->vars[pos]);
		while (pos != my_envs->len - 1)
		{
			my_envs->vars[pos] = my_envs->vars[pos + 1];
			pos++;
		}
	}
	my_envs->vars[pos] = NULL;
	my_envs->len--;
	return (0);
}
int	do_unset(t_args *expr, t_envs *my_envs)
{
	int	i;
	int	pos;

	i = 1;
	if (expr->len > 1)
	{
		while (i < my_envs->len && expr->args[i])
		{
			pos = pos_env_var(my_envs, expr->args[i]);
			if (pos < 0)
			{
				printf("'%s' could not be found\n", expr->args[i]);
				return (1);
			}
			else
				g_exit = remove_var(my_envs, pos);
			i++;
		}
	}
	else
	{
		printf("unset: invalid Syntax\n");
		return (1);
	}
	return (g_exit);
}
int	add_env(t_envs *envs, char *expr)
{
	size_t	i;
	int		pos;
	char	*key;

	i = 0;
	while (expr[i] && expr[i] != '=')
		i++;
	key = ft_substr(expr, 0, i);
	pos = pos_env_var(envs, key);
	if (pos == -1)
	{
		envs->len++;
		envs->vars = ft_realloc(envs->vars, envs->len);
		envs->vars[envs->len - 1] = ft_strdup(expr);
	}
	else
	{
		free(envs->vars[pos]);
		envs->vars[pos] = ft_strdup(expr);
	}
	envs->vars[envs->len] = NULL;
	free(key);
	return (0);
}
int	do_export(t_args *expr, t_envs *envs)
{
	int	i;

	if (expr->len == 1)
	{
		sort_envs(envs);
		return (0);
	}
	i = 1;
	while (expr->args[i])
	{
		if (expr->args[i] && isalnum(expr->args[i][0]))
			g_exit = add_env(envs, expr->args[i]);
		i++;
	}
	if (g_exit > 0)
		g_exit = 1;
	return (g_exit);
}
int	check_delim(t_args *expr)
{
	size_t	j;

	j = -1;
	while (++j < expr->len)
		if (ft_strcmp(expr->args[j], ">") == 0
			|| ft_strcmp(expr->args[j], "<") == 0
			|| ft_strcmp(expr->args[j], ">>") == 0
			|| ft_strcmp(expr->args[j], "<<") == 0
			|| ft_strcmp(expr->args[j], "|") == 0
			|| ft_strcmp(expr->args[j], "||") == 0)
			return (printf("Error: character is not allowed with echo\n"));
	return (0);
}
int	do_echo(t_args *expr)
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = 1;
	if (expr->len == 1)
		printf("\n");
	if (expr->args[1])
	{
		if (ft_strcmp(expr->args[1], "\\") == 0)
			return (0);
		if (ft_strncmp(expr->args[1], "-n", 2) == 0)
			i = 2;
		else
			i = 1;
	}
	if (check_delim(expr))
		return (1);
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
	if (expr->args[1])
		if (ft_strncmp(expr->args[1], "-n", 2) != 0)
			printf("\n");
	return (0);
}
int	digits_in(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isdigit(arg[0]) && !(arg[0] == '-') && !(arg[0] == '+'))
		return (1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i += 1;
	}
	return (0);
}

int	check_for_pipe(t_list *expressions)
{
   	while (expressions->next)
   	{
		t_args *expr = expressions->content;
		if (expr->state == PIPE)
		{
			printf("pipe found\n");
			return 1;
		}
		expressions = expressions->next;
    	}
	return 0;
}

int	do_exit(t_list *expressions, t_args *expr, t_params *params) //se houver pipe na expressao entao o exit nunca e executado
{
	long int mini_exit;

	mini_exit = 0;
	if (check_for_pipe(expressions))
		return (g_exit);
	printf("exit\n");
	if (expr->len >= 3)
	{
		mini_exit = 1;
		printf("exit: too many arguments\n");
	}
	else if (expr->len == 2)
	{
		if (digits_in((char *)expr->args[1]) || ft_atoi(expr->args[1]) > INT_MAX)
		{
			printf("%s: numeric argument required\n",
				(char *)expr->args[1]);
			mini_exit = 2;
		}
		else
			mini_exit = ft_atoi(expr->args[1]);
	}
	params->exited = 1;
	return ((int)mini_exit);
}
