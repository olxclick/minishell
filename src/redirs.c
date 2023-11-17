/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:58:35 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/14 13:58:48 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir_out(t_params *params)
{
	char	*line;

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

int	*create_files(t_list *expressions)
{
	t_args	*expr;
	t_state	prev_state;
	size_t	i;
	int		*files;
	int		n_files;

	i = 0;
	expr = expressions->content;
	n_files = count_files_needed(expressions);
	if (!n_files)
		return (NULL);
	files = malloc(sizeof(int) * n_files);
	while (expressions->next)
	{
		i = -1;
		expr = expressions->content;
		while (++i < expr->len)
		{
			if (expr->state == DOC)
				define_file(expr, &files[i], prev_state);
		}
		prev_state = expr->state;
		expressions = expressions->next;
	}
	return (files);
}

int	count_files_needed(t_list *expressions)
{
	t_args	*expr;
	int		count;

	count = 0;
	expr = expressions->content;
	while (expressions->next)
	{
		expr = expressions->content;
		if (expr->args[0])
		{
			if (ft_strcmp(expr->args[0], ">") == 0 || ft_strcmp(expr->args[0],
					">>") == 0)
				count++;
		}
		expressions = expressions->next;
	}
	return (count);
}

int	here(t_list *expressions, t_params *params, t_envs *envs, char *line)
{
	char	*delim;

	delim = get_heredoc_delim(expressions);
	if (check_vars(line))
	{
		line = check_line(line, envs);
		line = ft_strjoin(line, "\n");
	}
	if (heredoc_checker(line, delim))
	{
		free(delim);
		return (0);
	}
	if (ft_strcmp(((t_args *)expressions->content)->args[1], "<<") == 0)
		write(params->heredoc_fd, line, ft_strlen(line));
	if (line)
		free(line);
	free(delim);
	return (1);
}

int	do_heredoc(t_list *expressions, t_params *params, t_envs *envs, bool flag)
{
	char	*heredoc_line;
	char	*line;

	if (flag)
	{
		while (true)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &ft_here_sig);
			heredoc_line = readline("> ");
			line = ft_strjoin(heredoc_line, "\n");
			free(heredoc_line);
			if (!here(expressions, params, envs, line))
				break ;
		}
		params->heredoc_fd = open(".heredoc.tmp", O_RDONLY | 0644);
		params->input_fd = params->heredoc_fd;
		if (line)
			free(line);
	}
	return (0);
}
