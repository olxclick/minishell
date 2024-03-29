/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:07:58 by jbranco-          #+#    #+#             */
/*   Updated: 2024/01/15 18:45:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect(t_params *params, bool flag)
{
	if (params->input_fd != STDIN_FILENO && flag)
	{
		dup2(params->input_fd, STDIN_FILENO);
		close(params->input_fd);
	}
}

void	redir_input(t_list *expressions, t_params *params, bool is_to_do)
{
	t_args	*expr;
	int		flag;

	flag = 0;
	params->input_fd = 0;
	expr = expressions->content;
	while (expressions->next)
	{
		expr = expressions->content;
		if (flag && is_to_do && params->input_fd == STDIN_FILENO)
			params->input_fd = read_fd(expr->args[0]);
		if (expr->state == REDIR_IN && is_to_do)
			flag = 1;
		if (expr->state == REDIR_OUT || expr->state == REDIR_APPEND)
			do_redir_out(params);
		expressions = expressions->next;
	}
}

int	redir_needed(t_list *expressions)
{
	t_args	*expr;

	while (expressions->next)
	{
		expr = expressions->content;
		if (expr->state == REDIR_IN)
			return (1);
		else if (expr->state == HEREDOC)
			return (2);
		expressions = expressions->next;
	}
	return (0);
}

int	read_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("%s : No such file or directory\n", file_name);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_pipes(t_list *expressions, t_params *params)
{
	t_args	*nextexpr;

	nextexpr = NULL;
	if (expressions->next)
		nextexpr = expressions->next->content;
	if (nextexpr && nextexpr->state != HEREDOC && nextexpr->state != REDIR_IN)
	{
		close(params->pipe_fd[R]);
		if (params->input_fd != STDIN_FILENO)
		{
			dup2(params->input_fd, STDIN_FILENO);
			close(params->input_fd);
		}
		dup2(params->pipe_fd[W], STDOUT_FILENO);
		close(params->pipe_fd[W]);
	}
	else
	{
		if (params->input_fd != STDIN_FILENO)
		{
			dup2(params->input_fd, STDIN_FILENO);
			close(params->input_fd);
		}
	}
}
