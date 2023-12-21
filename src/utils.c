/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:59:58 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/21 17:20:15 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
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

int	find_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == SINGLE_QUOTE[0]
			|| str[i] == DOUBLE_QUOTE[0])
			return (i);
		i++;
	}
	return (i);
}

int	pos_env_var(t_envs *envs, char *find)
{
	int	i;
	int	end;

	i = 0;
	end = find_end(find);
	while (i < envs->len)
	{
		if (ft_strncmp(find, envs->vars[i], end) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	get_lenght(t_envs *envs, int i)
{
	int	j;

	j = 0;
	while (envs->vars[i][j])
	{
		if (envs->vars[i][j] == '=')
			return (j + 1);
		j++;
	}
	return (j);
}
