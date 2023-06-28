/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/28 14:28:39 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_args	*format_input(char *input)
{
	t_args *args;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 1;
	i = 0;
	j = 0;
	args = initialize_args();
	while ((input[i]) && (input[i] != ' ' && input[i] != '|' && input[i] != '>' && input[i] != '<'))
	{
		args->expression[0] = malloc((ft_strlen(input) + 1) * sizeof(char));
		ft_strcpy(args->expression[0], input);
		i++;
	}
	args->len++;
	if (input[i])
	{
		while (input[i])
		{
			if (input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<')
			{
				j = i++;
				while ((input[j]) && (input[j] != ' ' && input[j] != '|' && input[j] != '>' && input[j] != '<'))
				{
					args->expression[k] = malloc((strlen(input) + 1) * sizeof(char));
					ft_strcpy(args->expression[k], input + j);
					j++;
				}
			k++;
			args->len++;
			}
		}
		i++;
	}
	return (args);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
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
