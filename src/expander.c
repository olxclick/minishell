/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/03 18:03:24 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	conta o numero de $ encontrados na string e 
	retorna count
*/

char	*check_token(char *input, t_envs *envs)
{
	int	i;
	int	flag;

	i = 0;
	flag = is_same_quotes(input);
	printf("flag: %d\n", flag);
	if (flag < 0)
	{
		free(input);
		return (NULL);
	}
	input = remove_quotes(input);
	if ((flag == 1) || ft_strcmp(input, "$?") == 0 || input[i] == '$')
		input = get_var(input, envs);
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE && input[ft_strlen(input)
			- 1] == SINGLE_QUOTE)
		{
			input = redo_token(input, SINGLE_QUOTE);
			break ;
		}
		else if (input[i] == DOUBLE_QUOTE && input[ft_strlen(input)
				- 1] == DOUBLE_QUOTE)
		{
			input = redo_token(input, DOUBLE_QUOTE);
			break ;
		}
		i++;
	}
	return (input);
}

char	*expand_var(char *input, t_envs *envs, int x, char *res)
{
	int	start;
	int	j;
	int	pos;
	char	*buf;
	char	*buf2;

	j = 0;
	buf = NULL;
	buf2 = NULL;
	pos = search_var(envs, &input[x]);
	if (pos != -1)
	{
		while (envs->vars[pos][j] != '=')
			j++;
		start = j + 1;
		while (envs->vars[pos][j])
			j++;
		if (!res)
			res = ft_substr(envs->vars[pos], start, j);
		else
		{
			buf = ft_strdup(res);
			buf2 = ft_substr(envs->vars[pos], start, j);
			free(res);
			res = ft_strjoin(buf, buf2);
			free(buf);
			free(buf2);
		}
	}
	return (res);
}

char	*get_var(char *input, t_envs *envs)
{
	char	*res;
	char	*buf;
	char	*buf2;
	int	x;
	int	start;
	
	x = 0;
	res = NULL;
	buf = NULL;
	buf2 = NULL;
	if (ft_strcmp(input, "$?") == 0)
	{
		free(input);
		return (ft_itoa(g_exit));
	}
	while (input[x])
	{
		if (input[x] == '$')
		{
			res = expand_var(input, envs, x + 1, res);
			while (input[x] && input[x] != ' ')
				x++;
		}
		else
		{
			start = x;
			while (input[x] && input[x] != '$')
				x++;
			if (!res)
				res = ft_substr(input, start, x);
			else
			{
				buf = ft_strdup(res);
				free(res);
				buf2 = ft_substr(input, start, x - start);
				res = ft_strjoin(buf, buf2);
				free(buf);
				free(buf2);
			}
		}
		if (!input[x])
			break ;
	}
	if (!res)
		res = ft_strdup(input);
	free(input);
	return (res);
}

char	*redo_token(char *input, char c)
{
	int		start;
	char	*new_input;
	int		end;
	int		diff;

	start = 0;
	end = ft_strlen(input) - 1;
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
