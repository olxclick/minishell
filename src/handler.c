/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:07:58 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/28 18:11:40 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//if only pipe as input read memoryaccess segf
void	handle_pipes(t_list *expressions, t_params *params)
{
	if (expressions->next->content)
	{
        	//fechar read_end pois nao vai ser preciso
		close(params->pipe_fd[R]);
		if (params->input_fd != STDIN_FILENO)
		{
			dup2(params->input_fd, STDIN_FILENO);
			close(params->input_fd);
		}
        	//o que for escrito no STDOUT vai para pipe_fd[W]
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
		if (params->output_fd != STDOUT_FILENO)
		{
			dup2(params->output_fd, STDOUT_FILENO);
			close(params->output_fd);
		}
	}
}

void	handle_redirs(t_list *expressions, t_params *params) //handle < && >
{
	t_args *expr;

	expr = expressions->content;
	if (expr->state == REDIR_IN)
		do_redir_in(expr, params);
	else if (expr->state == REDIR_OUT)
		do_redir_out(expr, params);
	else if (expr->state == REDIR_APPEND)
		do_redir_append(expr, params);
	else if (expr->state == HEREDOC)
		do_heredoc(expr, params);
}

void	do_redir_in(t_args *expr, t_params *params)
{
	int	redir_pos;
	FILE * fp;

	redir_pos = ft_strchr(expr->args, '<');
	fp = fopen(ft_strjoin(expr->args[expr->len], ".txt"), "w+");
	fprintf(fp, expr->args);
	fclose(fp);
}

void	do_redir_out(t_args *expr, t_params *params)
{
	
}
void	do_redir_append(t_args *expr, t_params *params)
{
	
}
void	do_heredoc(t_args *expr, t_params *params)
{
	
}