/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/14 12:15:19 by jbranco-         ###   ########.fr       */
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

char	*var_fill(char *res, t_envs *envs, int pos)
{
	int		start;
	int		j;
	char	*buf;
	char	*buf2;

	j = 0;
	buf = NULL;
	buf2 = NULL;
	start = 0;
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
		free_buf(buf, buf2);
	}
	return (res);
}

char	*expand_var(char *input, t_envs *envs, int x, char *res)
{
	int		pos;
	char	*final;

	pos = pos_env_var(envs, &input[x]);
	if (pos != -1)
		final = var_fill(res, envs, pos);
	return (final);
}

char	*do_smth(char *res, char *input, t_envs *envs, int *x)
{
	char	*final;
	
	final = expand_var(input, envs, *x + 1, res);
	return (final);
}

char	*do_other(char *input, char *res, int *x)
{
	int		start;
	t_expander	expander;

	expander.buf2 = NULL;
	expander.buf = NULL;
	start = *x;
	while (input[*x] && input[*x] != '$')
		*x = *x + 1;
	if (!res)
		res = ft_substr(input, start, *x);
	else
	{
		expander.buf = ft_strdup(res);
		free(res);
		expander.buf2 = ft_substr(input, start, *x - start);
		res = ft_strjoin(expander.buf, expander.buf2);
		free_buf(expander.buf2, expander.buf);
	}
	return (res);
}

char	*get_var(char *input, t_envs *envs)
{
	char	*res;
	int		x;

	x = 0;
	res = NULL;
	while (input[x])
	{
		if (input[x] == '$')
		{
			res = do_smth(res, input, envs, &x);
			while (input[x] && input[x] != ' ' && input[x] != SINGLE_QUOTE && input[x] != DOUBLE_QUOTE)
			{
				x++;
				if (input[x] == '$')
					break ;
			}
		}
		else
			res = do_other(input, res, &x);
	}
	if (!res)
		res = ft_strdup(input);
	free(input);
	return (res);
}

char	*remove_quotes(char *input)
{
	int		i;
	char	*new_input;
	char	c;
	int		end;

	i = 0;
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
