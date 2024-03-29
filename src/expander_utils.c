/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:47:40 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/27 15:59:44 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input_unquoted(char *input, char c, int i, char *new_input)
{
	char	*buff;
	int		end;

	end = ft_strlen(input) - 1;
	while (input[end] != c)
		end--;
	while (input[end] == c)
		end--;
	buff = ft_substr(input, i, end - i + 1);
	end++;
	while (input[end] == c)
		end++;
	new_input = ft_strjoin(buff, &input[end]);
	free_buf(buff, input);
	return (new_input);
}

char	*remove_quotes(char *input)
{
	int		i;
	char	*new_input;
	char	c;
	int		end;

	i = 0;
	c = '\0';
	end = ft_strlen(input) - 1;
	new_input = NULL;
	if (input[i] == SINGLE_QUOTE[0] || input[i] == DOUBLE_QUOTE[0])
		c = input[i];
	while (input[i] && input[i] == c)
		i++;
	if (input[end] != c)
		return (get_input_unquoted(input, c, i, new_input));
	else
	{
		while (end >= i && input[end] == c)
			end--;
	}
	new_input = ft_substr(input, i, end - i + 1);
	free(input);
	return (new_input);
}

size_t	count_quotes(char *str)
{
	size_t	count;
	char	c;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	count = 0;
	c = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (flag && str[i] == c)
			count++;
		else if (str[i] == SINGLE_QUOTE[0] || str[i] == DOUBLE_QUOTE[0])
		{
			flag = 1;
			c = str[i];
			count++;
		}
		i++;
	}
	return (count);
}

char	*expand_var(char *input, t_envs *envs, int x, char *res)
{
	int		pos;
	char	*final;

	pos = pos_env_var(envs, &input[x]);
	if (pos < 0)
	{
		if (res)
		{
			final = ft_strdup(res);
			free(res);
		}
		else
			final = ft_strdup(input);
	}
	else
		final = var_fill(res, envs, pos);
	return (final);
}
