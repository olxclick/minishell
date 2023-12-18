/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/18 16:15:37 by jbranco-         ###   ########.fr       */
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

char	*do_smth(char *res, char *input, t_envs *envs, int *x)
{
	char	*final;

	final = expand_var(input, envs, *x + 1, res);
	return (final);
}

char	*do_other(char *input, char *res, int *x)
{
	int			start;
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
			while (input[x] && input[x] != ' ' && input[x] != SINGLE_QUOTE[0]
				&& input[x] != DOUBLE_QUOTE[0])
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
