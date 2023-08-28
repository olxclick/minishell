/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/28 16:12:23 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "exit") == 0) || (ft_strcmp(cmd, "$?") == 0) || (ft_strcmp(cmd, "env") == 0) || (ft_strcmp(cmd, "pwd") == 0) || (ft_strcmp(cmd, "cd") == 0)
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
		do_pwd();
	else if (ft_strcmp(expr->args[0], "$?") == 0)
		printf("%d\n", params->exit_status);
}

void	exec_parent_builtin(t_args *expr, t_params *params, t_envs *my_envs)
{
	if (ft_strcmp(expr->args[0], "exit") == 0)
		do_exit(expr, params);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		do_env(my_envs);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		do_export(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "unset") == 0)
		do_unset(expr, my_envs);
}

void	do_unset(t_args *expr, t_envs *my_envs)
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
				return ;
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
				return;
			}
			i++;
		}
	}
	else
		return ;
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

void	add_env(t_envs *envs, char *expr)
{
	size_t	i;
	int	pos;
	char	*key;

	i = 0;
	while (expr[i] && expr[i] != '=')
		i++;
	if (i == ft_strlen(expr))
		return ;
	if (!ft_isalnum(expr[i - 1]) || !ft_isalnum(expr[i + 1]))
	{
		printf("Error, please check your input\n");
		return ;
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

void	do_export(t_args *expr, t_envs *envs)
{
	int	i;

	if (expr->len == 1)
	{
		sort_envs(envs);
		return ;
	}
	i = 1;
	while (expr->args[i])
	{
		if (expr->args[i] && isalnum(expr->args[i][0]))
			add_env(envs, expr->args[i]);
		i++;
	}
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

void	do_env(t_envs *my_envs)
{
	int	i;

	i = 0;
	while (i < my_envs->len)
		printf("%s\n", my_envs->vars[i++]);
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
	printf("exit\n");
	if (expr->len >= 3)
		printf("too many arguments\n");
	else if (expr->len == 2)
	{
		params->exit_status = ft_atoi(expr->args[1]) % 256;
		
	}
	else
		params->exited = 1;
}
