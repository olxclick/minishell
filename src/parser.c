/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/13 13:38:07 by jbranco-         ###   ########.fr       */
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

void	parse_expr(t_args *expression, t_token t, int i)
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
}
