/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/05 16:56:55 by jbranco-         ###   ########.fr       */
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
			printf("hi1\n");
			token = operator_return(token, input, i);
			break ;
		}
		else if (input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			printf("hi2\n");
			token = ft_substr(input, 0, i);
			break ;
		}
		else if (input[i + 1] == '\0')
		{
			printf("hi3\n");
			token = ft_substr(input, 0, i + 1);
			break ;
		}
		i++;
	}
	printf("TOKEN PASSED TO CHECK_TOKEN: %s\n", token);
	token = check_token(token);
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

char	*check_token(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE && input[ft_strlen(input) - 1] == SINGLE_QUOTE)
		{
			input = redo_token(input, SINGLE_QUOTE);
			break ;
		}
		else if (input[i] == DOUBLE_QUOTE && input[ft_strlen(input) - 1] == DOUBLE_QUOTE)
		{	
			input = redo_token(input, DOUBLE_QUOTE);
			break ;
		}
		i++;
	}
	return (input);
}

char	*redo_token(char *input, char c)
{
	int	start = 0;
	char	*new_input;
	int	end = ft_strlen(input) - 1;
	int	diff;

	if (c == SINGLE_QUOTE)
	{
		while ((input[start] == SINGLE_QUOTE) && start <= end)
			start++;
		while ((input[end] == SINGLE_QUOTE) && end >= start)
			end--;
		diff = ft_strlen(input) - 1 - end;
	}
	else
	{
		while ((input[start] == DOUBLE_QUOTE) && start <= end)
			start++;
		while ((input[end] == DOUBLE_QUOTE) && end >= start)
			end--;
		diff = ft_strlen(input) - 1 - end;
	}
	if (start > end || diff != start)
		return (input);
	new_input = ft_substr(input, start, end - start + 1);
	new_input[end - start + 1] = '\0';
	free(input);
	return (new_input);
}

size_t	count_quotes(char *str)
{
	int	i;
	int	flag;
	size_t	count;
	char	c;

	i = 0;
	flag = 0;
	count = 0;
	while (str[i])
	{
		if (flag)
		{
			if (str[i] == c)
				count++;
		}
		else if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			flag = 1;
			c = str[i];
			count++;
		}
		i++;
	}
	return (count);
}

t_token set_args_tokens(char *input)
{
	char *token;
	size_t j = 0;
	size_t	n_quotes = 0;
	t_token t;

	t.token = malloc(1 * sizeof(char *));
	while (*input && *input == ' ')
		input++;
	n_quotes = count_quotes(input);
	while (1 && *input)
	{
		token = get_token(input);
		t.token[j] = token;
		j++;
		t.token = ft_realloc(t.token, j + 1);
		if (ft_strlen(input) <= ft_strlen(token))
			break ;
		printf("Cur_Input: %s\n", input);
		input += ft_strlen(token) + n_quotes; //echo problem is here
		printf("Cur_Input: %s\n", input);
		while (*input && *input == ' ')
			input++;
	}
	t.token[j] = NULL;
	return (t);
}
