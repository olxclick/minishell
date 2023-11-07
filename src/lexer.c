/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/07 11:41:57 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token(char *input)
{
	int		i;
	bool	in_quote;

	i = 0;
	in_quote = false;
	if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
	{
		if (!in_quote)
			in_quote = true;
		else
			in_quote = false;
	}
	while (input[i])
	{
		if (i == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<'))
			return (operator_return(input, i));
		else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>'
				|| input[i] == '<') && !in_quote)
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
	int		i;
	size_t	count_s;
	size_t	count_d;
	char	c;

	i = 0;
	count_s = 0;
	count_d = 0;
	c = '\0';
	if (str[0] == SINGLE_QUOTE || str[0] == DOUBLE_QUOTE)
		c = str[0];
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE && c == SINGLE_QUOTE)
			count_s++;
		if (str[i] == DOUBLE_QUOTE && c == DOUBLE_QUOTE)
			count_d++;
		i++;
	}
	if ((count_s % 2 != 0 && c == SINGLE_QUOTE)
		|| (count_d % 2 != 0 && c == DOUBLE_QUOTE))
		return (printf("error: unclosed quotes!\n"));
	if (str[0] == SINGLE_QUOTE)
		return (2);
	else if (str[0] == DOUBLE_QUOTE)
		return (1);
	return (0);
}

t_token	set_args_tokens(char *input, t_envs *envs)
{
	char	*token;
	size_t	j;
	size_t	size;
	t_token	t;

	j = 0;
	t.token = malloc(1 * sizeof(char *));
	while (*input && *input == ' ')
		input++;
	while (1 && *input)
	{
		token = get_token(input);
		size = ft_strlen(token);
		token = check_token(token, envs);
		if (!token)
			break ;
		t.token[j++] = token;
		t.token = ft_realloc(t.token, j + 1);
		if (ft_strlen(input) <= size)
			break ;
		input += size;
		while (*input && *input == ' ')
			input++;
	}
	t.token[j] = NULL;
	return (t);
}
