/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:58:35 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/29 17:57:19 by jbranco-         ###   ########.fr       */
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
		line = get_next_line(params->files[i]);
		if (line)
		{
			write(1, line, ft_strlen(line));
			free(line);
		}
		else
			break ;
	}
}

void	define_file(t_args *expr, int files)
{
	if (expr->state == REDIR_OUT)
		files = open(expr->args[expr->len], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		files = open(expr->args[expr->len], O_WRONLY | O_APPEND, 0644);
}

int	*create_files(t_args *expr)
{
	int	*files;
	int	n_files;
	int	i;

	n_files = count_files_needed(expr);
	files = malloc(sizeof(int) * n_files);
	printf("INSIDE CREATE FILES\n");
	while (i < expr->len)
	{
		if (expr->state == REDIR_OUT || expr->state == REDIR_APPEND)
			define_file(expr, files[i]);
		i++;
	}
	return (files);
}

int	count_files_needed(t_args *expr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (expr->args[i] < expr->len)
	{
		if (expr->args[i] == '>' && expr->args[i + 1] == '>')
			count++;
		else if (expr->args[i] == '<' && expr->args[i + 1] == '<')
			count++;
		else if (expr->args[i] == '>' || expr->args[i] == '<')
			count++;
		i++;
	}
	return (count);
}
