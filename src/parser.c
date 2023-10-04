/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/04 14:51:15 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_args(t_token t, int end)
{
	int		i;
	char	**args;

	i = 0;
	args = malloc((end + 1) * sizeof(char *));
	while (i < end)
	{
		args[i] = ft_strdup(t.token[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_list	*get_all_tokens(t_token t)
{
	t_list	*head;
	t_args	*expr;

	expr = get_parsed(t);
	if (!expr)
		return (NULL);
	if (((expr->len == 1) && (ft_strcmp(expr->args[0], "|") == 0
				|| ft_strcmp(expr->args[0], "||") == 0
				|| ft_strcmp(expr->args[0], ">>") == 0
				|| ft_strcmp(expr->args[0], "<<") == 0)))
	{
		printf("Expression error.\n");
		free_token(expr->args);
		free(expr);
		return (NULL);
	}
	head = ft_lstnew(expr);
	while (expr)
	{
		t.token += expr->len;
		expr = get_parsed(t);
		ft_lstadd_back(&head, ft_lstnew(expr));
	}
	return (head);
}

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
			if (i == 0)
			{
				expression->args = get_args(t, 1);
				expression->len = 1;
			}
			else
			{
				expression->args = get_args(t, i + 1);
				if (!t.token[i + 1])
					expression->len = i + 1;
				else
					expression->len = i;
			}
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
