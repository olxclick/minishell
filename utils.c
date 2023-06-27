/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/27 15:10:16 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		args->expression[0][i] = input[i];
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
					args->expression[k][j] = input[j];
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