/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/28 00:58:12 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_args(t_token t, int end)
{
	int i;
    	char **args;

	i = 0;
    	args = malloc((end + 2) * sizeof(char *));
	while (i <= end)
	{
		args[i] = ft_strdup(t.token[i]);
		printf("Args created: %s\n", args[i]);
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
		if ((is_delim(t.token[i])) || (!t.token[i + 1]))
		{
			// printf("OU E DELIM OU NAO EXISTE PROXIMO: %s\n", t.token[i]);
			expression->len = i + 1;
			expression->args = get_args(t, i);
			expression->state = get_state(expression, prev_state);
			prev_state = expression->state;
			printf("STATE: %d\n", expression->state);
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
      		state = get_delim_state(expression->args[0]);
	else
		state = CMD;
	return (state);
}

t_state	get_delim_state(char *token)
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
