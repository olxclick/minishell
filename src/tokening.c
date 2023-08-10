/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokening.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/10 13:42:20 by jbranco-         ###   ########.fr       */
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
		if (i == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<'))
		{
			token = operator_return(token, input, i);
			break ;
		}
		else if (input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			token = ft_substr(input, 0, i);
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
		token = ft_substr(input, 0, sizeof("|") - 1);
	else if (input[i] == '>' && input[i + 1] == '>')
		token = ft_substr(input, 0, sizeof(">>") - 1);
	else if (input[i] == '<' && input[i + 1] == '<')
		token = ft_substr(input, 0, sizeof("<<") - 1);
	else if (input[i] == '>')
		token = ft_substr(input, 0, sizeof(">") - 1);
	else if (input[i] == '<')
		token = ft_substr(input, 0, sizeof("<") - 1);
	return (token);
}

char	**ft_realloc(char **str, size_t new_size)
{
	char	**new_str;
	size_t	i;

	new_str = (char **)malloc(new_size * sizeof(char *));
	if (!new_str)
		return (0);
	i = 0;
	if (new_size > 1)
	{
		while (i < new_size - 1)
		{
			new_str[i] = str[i];
			i++;
		}
	}
	new_str[new_size - 1] = NULL;
	free(str);
	return (new_str);
}

t_token set_args_tokens(char *input)
{
	char *token;
	size_t j = 0;
	t_token t;
	
	t.token = malloc(1 * sizeof(char *));
	while (*input && *input == ' ')
		input++;
	while (1 && *input)
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

