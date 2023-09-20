/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/20 15:02:00 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "exit") == 0) || (ft_strcmp(cmd, "env") == 0) || (ft_strcmp(cmd, "pwd") == 0) || (ft_strcmp(cmd, "cd") == 0)
        || (ft_strcmp(cmd, "echo") == 0) || (ft_strcmp(cmd, "export") == 0 || (ft_strcmp(cmd, "unset") == 0));
}

int	do_pwd()
{
	char	cwd[PATH_MAX];

	printf("%s\n", getcwd(cwd, PATH_MAX));
	return (0);
}

int	exec_child_builtin(t_args *expr, t_params *params)
{
	(void)params;
	if (ft_strcmp(expr->args[0], "echo") == 0)
		g_exit = do_echo(expr);
	else if (ft_strcmp(expr->args[0], "pwd") == 0)
		g_exit = do_pwd();
	return (g_exit);
}

int	exec_parent_builtin(t_args *expr, t_params *params, t_envs *my_envs)
{
	if (ft_strcmp(expr->args[0], "exit") == 0)
		g_exit = do_exit(expr, params);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		g_exit = do_env(my_envs);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "unset") == 0)
		g_exit = do_unset(expr, my_envs);
	return (g_exit);
}

int	do_unset(t_args *expr, t_envs *my_envs)
{
	int	i;
	int	pos;

	i = 1;
	if (expr->len > 1)
	{
		while (i < my_envs->len)
		{
			pos = pos_env_var(my_envs, expr->args[i]);
			if (pos < 0)
			{
				printf("'%s' could not be found\n", expr->args[i]);
				return (1);
			}
			else
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
					my_envs->vars[pos] = NULL;
				}
				my_envs->len--;
				return (0);
			}
			i++;
		}
	}
	else
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	return (0);
}

int	search_var(t_envs *envs, char *to_find)
{
	int	size;
	int	i;

	i = 0;
	size = envs->len - 1;
	while (i < size)
	{
		if (ft_strncmp(envs->vars[i], to_find, ft_strlen(to_find) - 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	add_env(t_envs *envs, char *expr)
{
	size_t	i;
	int	pos;
	char	*key;

	i = 0;
	while (expr[i] && expr[i] != '=')
		i++;
	if (i == ft_strlen(expr))
		return (1);
	if (!ft_isalnum(expr[i - 1]) || !ft_isalnum(expr[i + 1]))
	{
		printf("export: bad input\n");
		return (1);
	}
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
	free(key);
	return (0);
}

int	pos_env_var(t_envs *envs, char *find)
{
	int	i;
	int	equal_sign;

	i = 0;
	equal_sign = 0;
	while (find[equal_sign] && find[equal_sign] != '=')
		equal_sign += 1;
	while (i < envs->len)
	{
		if (ft_strncmp(find, envs->vars[i], equal_sign) == 0)
			return (i);
		i++;
	}
	return (-1);
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
	return (g_exit);
}

void	envs_printer(t_envs *envs)
{
	int	i;
	int	j;
	int	flag;
	char	c;

	c = '"';
	i = 0;
	flag = 0;
	while (i < envs->len)
	{
		j = 0;
		printf("declare -x ");
		while (envs->vars[i][j])
		{
			if (envs->vars[i][j] == '=' || !envs->vars[i][j + 1])
				flag = 1;
			printf("%c", envs->vars[i][j]);
			if (flag)
				printf("%c", c);
			flag = 0;
			j++;
		}
		printf("\n");
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
	while (envs[i] != NULL)
		i++;
	return (i);
}

int	do_env(t_envs *my_envs)
{
	int	i;

	i = 0;
	while (i < my_envs->len)
		printf("%s\n", my_envs->vars[i++]);
	return (0);
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

int	do_echo(t_args *expr) // add condition for "echo $?" which should print exit status
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = 1;
	if (expr->args[1])
		i = (ft_strcmp(expr->args[1], "-n") == 0) ? 2 : 1;
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
		(ft_strcmp(expr->args[1], "-n") != 0) ? printf("\n") : 0;
	return (0);
}

int	do_exit(t_args *expr, t_params *params)
{
	int	mini_exit;

	mini_exit = 0;
	printf("exit\n");
	if (expr->len >= 3)
	{
		mini_exit = 1;
		printf("exit: too many arguments\n");
	}
	else if (expr->len == 2)
	{
		mini_exit = ft_atoi(expr->args[1]) % 256;
		params->exited = 1;
	}
	else
		params->exited = 1;
	return (mini_exit);
}
