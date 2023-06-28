/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/28 15:47:29 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_args	*format_input(char *input)
{
	t_args *args;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*full_token;

	k = 0;
	i = 0;
	j = 0;
	args = initialize_args();
	full_token = malloc((ft_strlen(input) + 1) * sizeof(char));
	ft_strlcpy(full_token, input, ft_strlen(input) + 1);
	if (full_token[i])
	{
		while (full_token[i])
		{
			while ((full_token[j]) && full_token[j] != '|' && full_token[j] != '>' && full_token[j] != '<')
				j++;
			if (j > i)
			{
				args->expression[k] = malloc(sizeof(char) * (j - i) + 1);
				ft_strlcpy(args->expression[k], &full_token[i], (j - i) + 1);
				k++;
				args->len++;
			}
			i = j;
		}
	}
	free(full_token);
	return (args);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_args	*initialize_args()
{
	t_args *args = malloc(sizeof(t_args));
	int	i;

	i = 0;
	args->len = 0;
	while (i < MAX_ARGS)
		args->expression[i++] = NULL;
	return (args);
}
