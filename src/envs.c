/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasferre <vasferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:32:41 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/05 15:18:50 by vasferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_envs(char **envs)
{
	char	**my_envs;
	int		i;

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

int	do_env(t_envs *my_envs)
{
	int	i;

	i = 0;
	while (i < my_envs->len)
		printf("%s\n", my_envs->vars[i++]);
	return (0);
}

t_envs	*copy_envs(t_envs *new_envs, t_envs *envs)
{
	int	i;

	i = 0;
	new_envs->len = envs->len;
	new_envs->vars = malloc(envs->len * sizeof(char *));
	new_envs->oldpwd = NULL;
	while (i < envs->len)
	{
		new_envs->vars[i] = ft_strdup(envs->vars[i]);
		i++;
	}
	return (new_envs);
}

void	sort_envs(t_envs *envs)
{
	t_envs	*envs_copy;
	int		i;
	int		j;

	i = 0;
	envs_copy = malloc(sizeof(t_envs));
	envs_copy = copy_envs(envs_copy, envs);
	while (i < envs->len)
	{
		j = 0;
		while (j < envs->len - i - 1)
		{
			if (strcmp(envs_copy->vars[j], envs_copy->vars[j + 1]) > 0)
				swap(&envs_copy->vars[j], &envs_copy->vars[j + 1]);
			j++;
		}
		i++;
	}
	envs_printer(envs_copy);
	copy_free(envs_copy);
}

void	envs_printer(t_envs *envs)
{
	int		i;
	int		j;
	int		flag;
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
