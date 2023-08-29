/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:58:35 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/29 12:40:45 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir_out(int read_fd, int fd) //reads from a file
{
	char	*line;

	while(1)
	{
		line = get_next_line(read_fd);
		if (line)
		{
			write(fd, line, ft_strlen(line));
			free(line);
		}
		else
			break ;
	}
	close(fd);
}

// int	*create_files(t_args *expr, int flag)
// {
// 	int	*files;
// 	int	n_files;
// 	int	i;

// 	i = 0;
// 	n_files = count_files_needed(expr);
// 	files = malloc(sizeof(int) * n_files);
// 	while (i < n_files)
// 	{
// 		if (flag == W)
// 			files[i] = open(ft_strjoin(expr->args[expr->len], ".txt"), flag);
// 		else
// 			files[i] = open(ft_strjoin(expr->args[expr->len], ".txt"), flag);
// 		i++;
// 	}
// 	return (files);
// }

// int	count_files_needed(t_args *expr) //only in some state this will be needed
// {
// 	int	redir_pos;
// 	int	count;

// 	redir_pos = ft_strchr(expr->args, '<');
// 	while (expr->args[redir_pos] < expr->len)
// 		count++;
// 	return (count);
// }

// void	do_redir_in(t_args *expr, t_params *params)
// {
// 	int	redir_pos;

// 	redir_pos = ft_strchr(expr->args, '<');
// 	create_files(expr, W);
// }
