/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:58:35 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/30 16:45:17 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir_out(t_params *params) //reads from a file
{
	char	*line;
	int	i;

	i = 0;
	while (1)
	{
		line = get_next_line(params->input_fd);
		if (line)
		{
			write(params->files[0], line, ft_strlen(line));
			free(line);
		}
		else
			break ;
	}
}

void	define_file(t_args *expr, int *files, t_state prev_state)
{
	if (prev_state == REDIR_OUT)
		*files = open(expr->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*files = open(expr->args[0], O_WRONLY | O_APPEND, 0644);
}

int	*create_files(t_list *expressions)
{
	t_args	*expr;
	t_state prev_state;
	size_t	i;
	int	*files;
	int	n_files;

	i = 0;
	expr = expressions->content;
	n_files = count_files_needed(expressions);
	if (!n_files)
		return (NULL);
	files = malloc(sizeof(int) * n_files);
	while (expressions->next)
	{
		i = 0;
		expr = expressions->content;
		while (i < expr->len)
		{
			if (expr->state == DOC)
				define_file(expr, &files[i], prev_state);
			i++;
		}
		prev_state = expr->state;
		expressions = expressions->next;
	}
	return (files);
}

int	count_files_needed(t_list *expressions)
{
	t_args *expr;
	int	count;

	count = 0;
	expr = expressions->content;
	while (expressions->next)
	{
		expr = expressions->content;
		if (expr->args[0])
		{
			if (ft_strcmp(expr->args[0], ">") == 0
				|| ft_strcmp(expr->args[0], ">>") == 0)
				count++;
		}
		expressions = expressions->next;
	}
	return (count);
}
