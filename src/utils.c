/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 17:58:27 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token(char *input)
{
	int	i;
	char    *token;

	i = 0;
	token = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			token = ft_substr(input, 0, i);
			break ;
		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			token = operator_return(token, input, i);
			break ;
		}
		//ultima palavra
		else if (input[i + 1] == '\0')
		{
			token = ft_substr(input, 0, i + 1);
			break ;
		}
		i++;
	}
	return (token);
}

char	*operator_return(char *token, char *input, int i)
{
	if (input[i] == '|')
		token = ft_substr(input, 0, sizeof("|"));
	else if (input[i] == '>')
		token = ft_substr(input, 0, sizeof(">"));
	else if (input[i] == '<')
		token = ft_substr(input, 0, sizeof("<"));
	return (token);
}

char	**ft_realloc(char **old_map, size_t new_size)
{
	char	**new_map;
	size_t	i;

	new_map = (char **)malloc(new_size * sizeof(char *));
	if (!new_map)
		return (0);
	i = 0;
	if (new_size > 1)
	{
		while (i < new_size - 1)
		{
			new_map[i] = old_map[i];
			i++;
		}
	}
	new_map[new_size - 1] = NULL;
	free(old_map);
	return (new_map);
}

t_token set_args_tokens(char *input)
{
	char *token;
	size_t j = 0;
	t_token t;
	
	t.token = malloc(1 * sizeof(char *));
	while (*input && *input == ' ')
		input++;
	while (1)
	{
		token = get_token(input);
		t.token[j] = token;
		j++;
		t.token = ft_realloc(t.token, j + 1);
		if (ft_strlen(input) <= ft_strlen(token))
			break ;
		input += ft_strlen(token);
		while (*input && *input == ' ')
			input++;
	}
	t.token[j] = NULL; // Set the last element to NULL to mark the end
	return (t);
}

void	check_builtin(t_args *args, t_pid *proccess)
{
	if (ft_strcmp(args->args[0], "exit") == 0)
		exit_function(args, proccess);
}
