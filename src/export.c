/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:47:29 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/20 12:54:21 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    adiciona ou da update as variaveis
    pega o nome da variavel atraves da "envs"
    encontra a sua posicao e adiciona ou da update
    na variavel
*/
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
	free(key);
	return (0);
}

int	do_export(t_args *expr, t_envs *envs, bool flag)
{
	int	i;

	if (expr->len == 1)
	{
		if (flag)
			sort_envs(envs);
		return (0);
	}
	i = 1;
	while (expr->args[i] && flag)
	{
		if (expr->args[i] && isalnum(expr->args[i][0]))
			g_exit = add_env(envs, expr->args[i]);
		i++;
	}
	if (g_exit > 0)
		g_exit = 1;
	return (g_exit);
}

/*
    remove variaves numa posicao exata na estrutura
    "my_envs", da tambem update na lista
*/

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

/*
    percorre pelas variaveis , encontra a posicao
    e remove-as. caso o nome nao seja especificado ou
    nao seja encontrado da return de 0
*/
int	do_unset(t_args *expr, t_envs *my_envs, bool flag)
{
	int	i;
	int	pos;

	i = 1;
	g_exit = 1;
	if (expr->len > 1)
	{
		while (i < my_envs->len && expr->args[i])
		{
			pos = pos_env_var(my_envs, expr->args[i]);
			if (pos <= 0)
			{
				if (flag)
					printf("'%s' could not be found\n", expr->args[i]);
			}
			else if (flag)
				g_exit = remove_var(my_envs, pos);
			i++;
		}
	}
	else
		if (flag)
			printf("unset: invalid Syntax\n");
	return (g_exit);
}

void	copy_free(t_envs *my_envs)
{
	int	i;

	i = 0;
	if (my_envs)
	{
		if (my_envs->vars)
		{
			while (i < my_envs->len)
			{
				if (my_envs->vars[i])
					free(my_envs->vars[i]);
				i++;
			}
			if (my_envs->oldpwd)
				free(my_envs->oldpwd);
			if (my_envs->pwd)
				free(my_envs->pwd);
			free(my_envs->vars);
		}
		free(my_envs);
	}
}
