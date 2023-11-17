/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/13 13:00:51 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if ((count_s % 2 != 0 && c == SINGLE_QUOTE) || (count_d % 2 != 0
			&& c == DOUBLE_QUOTE))
		return (printf("error: unclosed quotes!\n"));
	return (quote_return(str));
}

t_token	set_args_tokens(char *input, t_envs *envs, t_token t)
{
	char	*token;
	size_t	j;
	size_t	size;

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
