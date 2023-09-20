/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/20 15:01:29 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token(char *input)
{
	int	i;
	bool	in_quote;

	i = 0;
	in_quote = false;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
			in_quote = !in_quote ? true : false;
		if (i == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<') && !in_quote)
			return (operator_return(input, i));
		else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !in_quote)
			return (ft_substr(input, 0, i));
		else if (input[i + 1] == '\0')
			return (ft_substr(input, 0, i + 1));
		i++;
	}
	return (NULL);
}

char	*operator_return(char *input, int i)
{
	char	*token;

	token = NULL;
	if (input[i] == '|' && input[i + 1] == '|')
		token = ft_substr(input, 0, sizeof("||") - 1);
	else if (input[i] == '|')
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

int	is_same_quotes(char *str)
{
	int	i;
	size_t	countS;
	size_t	countD;
	
	countS = 0;
	countD = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
			countS++;
		else if (str[i] == DOUBLE_QUOTE)
			countD++;
		i++;
	}
	if ((countS % 2 == 0 && countS != 0) || (countD % 2 == 0 && countD != 0))
		return (countS == count_quotes(str) || countD == count_quotes(str));
	return (0);
}

char	*check_token(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = is_same_quotes(input);
	while (input[i])
	{
		if (flag)
			return (remove_quotes(input));
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
	free(input);
	return (new_input);
}

char	*remove_quotes(char *input)
{
	int	i = 0;
	int	j = 0;
	int	len = ft_strlen(input);
	char	*new_input = (char *)malloc(len + 1);

	while (i < len)
	{
		if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			while (input[i] && (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE))
				i++;
			while (i < len && (input[i] != SINGLE_QUOTE && input[i] != DOUBLE_QUOTE))
				new_input[j++] = input[i++];
		}
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
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
		if (flag && str[i] == c)
			count++;
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
	while (1 && *input)
	{
		token = get_token(input);
		n_quotes = count_quotes(token);
		token = check_token(token);
		t.token[j] = token;
		j++;
		t.token = ft_realloc(t.token, j + 1);
		if (ft_strlen(input) <= ft_strlen(token))
			break ;
		input += ft_strlen(token) + (n_quotes - count_quotes(token)); //echo problem is here
		while (*input && *input == ' ')
			input++;
	}
	t.token[j] = NULL;
	return (t);
}
