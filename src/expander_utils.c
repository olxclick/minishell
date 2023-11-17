/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:48:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/14 12:15:19 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*expand_var(char *input, t_envs *envs, int x, char *res)
{
	int		pos;
	char	*final;

	pos = pos_env_var(envs, &input[x]);
	if (pos != -1)
		final = var_fill(res, envs, pos);
	return (final);
}
