/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:07:58 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 00:40:19 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipes(t_list *expressions, t_params params)
{
	if (expressions->next)
	{
        	//fechar read_end pois nao vai ser preciso
		close(params.pipe_fd[R]);
		if (params.input_fd != STDIN_FILENO)
		{
			dup2(params.input_fd, STDIN_FILENO);
			close(params.input_fd);
		}
        	//o que for escrito no STDOUT vai para pipe_fd[W]
		dup2(params.pipe_fd[W], STDOUT_FILENO);
		close(params.pipe_fd[W]);
	}
	else
	{
		if (params.input_fd != STDIN_FILENO)
		{
			dup2(params.input_fd, STDIN_FILENO);
			close(params.input_fd);
		}
		if (params.output_fd != STDOUT_FILENO)
		{
			dup2(params.output_fd, STDOUT_FILENO);
			close(params.output_fd);
		}
	}
}
