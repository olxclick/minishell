/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/10 12:49:02 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_token(char *input, t_envs *envs)
{
	int	i;
	int	flag;

	i = 0;
	flag = is_same_quotes(input);
	if (input[0] == '$')
		return (get_var(input, envs));
	while (input[i])
	{
		if (flag > 0)
			return (remove_quotes(input));
		if (input[i] == SINGLE_QUOTE && input[ft_strlen(input)
				- 1] == SINGLE_QUOTE)
		{
			input = redo_token(input, SINGLE_QUOTE, flag, envs);
			break ;
		}
		else if (input[i] == DOUBLE_QUOTE && input[ft_strlen(input)
				- 1] == DOUBLE_QUOTE)
		{
			input = redo_token(input, DOUBLE_QUOTE, flag, envs);
			break ;
		}
		i++;
	}
	return (input);
}
char	*get_var(char *input, t_envs *envs)
{
	char	*res;
	int		j;
	int		start;
	int		pos;

	j = 0;
	pos = search_var(envs, &input[1]);
	if (ft_strcmp(input, "$?") == 0)
		res = ft_itoa(g_exit);
	else
	{
		if (pos == -1)
		{
			free(input);
			return (NULL);
		}
		while (envs->vars[pos][j] != '=')
			j++;
		start = j + 1;
		while (envs->vars[pos][j])
			j++;
		res = ft_substr(envs->vars[pos], start, j);
	}
	free(input);
	return (res);
}
char	*redo_token(char *input, char c, int flag, t_envs *envs)
{
	int		start;
	char	*new_input;
	int		end;
	int		diff;

	start = 0;
	end = ft_strlen(input) - 1;
	if (flag == -1)
		return (get_var(remove_quotes(input), envs));
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
	int		i;
	int		j;
	int		len;
	char	*new_input;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	new_input = (char *)malloc(len + 1);
	while (i < len)
	{
		if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			while (input[i] && (input[i] == SINGLE_QUOTE
					|| input[i] == DOUBLE_QUOTE))
				i++;
			while (i < len && (input[i] != SINGLE_QUOTE
					&& input[i] != DOUBLE_QUOTE))
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
