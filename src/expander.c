/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/06 16:42:53 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_token(char *input, t_envs *envs)
{
	int	i;
	int	flag;

	i = 0;
	flag = is_same_quotes(input);
	if (flag > 2)
	{
		free(input);
		return (NULL);
	}
	if (flag == 1 || flag == 2)
		input = remove_quotes(input);
	if (ft_strcmp(input, "$?") == 0)
	{
		free(input);
		return (ft_itoa(g_exit));
	}
	if (flag == 1 || (input[i] == '$' && flag == 0))
		input = get_var(input, envs);
	return (input);
}

char	*expand_var(char *input, t_envs *envs, int x, char *res)
{
	int		start;
	int		j;
	int		pos;
	char	*buf;
	char	*buf2;

	j = 0;
	buf = NULL;
	buf2 = NULL;
	pos = pos_env_var(envs, &input[x]);
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
	int		x;
	int		start;

	x = 0;
	res = NULL;
	buf = NULL;
	buf2 = NULL;
	while (input[x])
	{
		if (input[x] == '$')
		{
			res = expand_var(input, envs, x + 1, res);
			while (input[x] && input[x] != ' ' && input[x] != SINGLE_QUOTE && input[x] != DOUBLE_QUOTE)
			{
				x++;
				if (input[x] == '$')
					break ;
			}
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

char	*remove_quotes(char *input)
{
	int		i;
	int		j;
	char	*new_input;
	char	c;
	int		end;

	i = 0;
	j = 0;
	c = '\0';
	if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		c = input[i];
	end = ft_strlen(input) - 1;
	while (input[i] && (input[i] == c || input[i] == c))
		i++;
	while (input[end] && (input[end] == c || input[end] == c))
		end--;
	new_input = ft_substr(input, i, end);
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
