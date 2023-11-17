/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:48:07 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/17 11:48:12 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_args	*get_parsed(t_token t)
{
	t_args			*expression;
	int				i;
	static t_state	prev_state = DEFAULT;

	i = 0;
	expression = malloc(sizeof(t_args));
	while (t.token[i])
	{
		if ((is_delim(t.token[i])) || (!t.token[i + 1]))
		{
			parse_expr(expression, t, i);
			expression->state = get_state(expression, prev_state);
			prev_state = expression->state;
			return (expression);
		}
		i++;
	}
	free(expression);
	return (NULL);
}

t_state	get_state(t_args *expression, t_state prev_state)
{
	t_state	state;

	if (prev_state >= 2 && prev_state <= 4)
		state = DOC;
	else if (expression->len == 1 && is_delim(expression->args[0]))
		state = get_delim_state(expression->args[0]);
	else
		state = CMD;
	return (state);
}

t_state	get_delim_state(char *token)
{
	t_state	state;

	state = DEFAULT;
	if (ft_strcmp(token, "|") == 0)
		state = PIPE;
	else if (ft_strcmp(token, ">") == 0)
		state = REDIR_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		state = REDIR_APPEND;
	else if (ft_strcmp(token, "<") == 0)
		state = REDIR_IN;
	else if (ft_strcmp(token, "<<") == 0)
		state = HEREDOC;
	return (state);
}
