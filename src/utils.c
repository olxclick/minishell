/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:59:58 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/05 13:45:34 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int	search_var(t_envs *envs, char *find)
{
	int	i;

	i = 0;
	while (i < envs->len)
	{
		if (ft_strncmp(find, envs->vars[i], get_lenght(envs, i) - 1) == 0)
			return (i);
		i++;
	}
	return (-1);
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
int	get_lenght(t_envs *envs, int i)
{
	int	j;

	j = 0;
	while(envs->vars[i][j])
	{
		if (envs->vars[i][j] == '=')
			return (j + 1);
		j++;
	}
	return (j);
}
