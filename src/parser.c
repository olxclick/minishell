/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 15:49:45 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_args(t_token t, int end)
{
	int i;
    	char **args;

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

t_list    *get_all_tokens(t_token t)
{
	t_list *head;
	t_args *expr;

	expr = get_parsed(t);
	head = ft_lstnew(expr);
	while (expr)
	{
		t.token += expr->len; //passar para o/os proximo token
		expr = get_parsed(t);
		ft_lstadd_back(&head, ft_lstnew(expr));//adicionar a nova expressão à lista
	}
	return (head);
}

t_args    *get_parsed(t_token t)
{
    	t_args *expression;
	int	i;
    	static t_state prev_state = DEFAULT;

	i = 0;
    	expression = malloc(sizeof(t_args));
	while (t.token[i])
	{//[ls] [a]  [|] [wc] 
		if (is_delim(t.token[i]) || !t.token[i + 1])
		{
			//copia o ultimo
			expression->len = i;
			if (i == 0)
			{
				expression->len = 1;
				expression->args = get_args(t, 1);
			}
			//more than one args
			else
				expression->args = get_args(t, i);
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
   	t_state state;

	if (prev_state >= 2 && prev_state <= 5)
		state = DOC;
	else if (expression->len == 1 && is_delim(expression->args[0]))
      		state = get_delim(expression->args[0]);
	else
		state = CMD;
	return (state);
}

t_state	get_delim(char *token)
{
	t_state state;

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
