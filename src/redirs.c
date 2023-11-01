/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:58:35 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/01 14:03:03 by jbranco-         ###   ########.fr       */
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

void	define_file(t_args *expr, int *files, t_state prev_state)
{
	if (prev_state == REDIR_OUT)
		*files = open(expr->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*files = open(expr->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	heredoc_checker(char *line, char *delim)
{
	if (!line)
		return (1);
	else if (ft_strcmp(line, "\n") == 0)
		return (0);
	else if (ft_strncmp(line, delim, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

char	*get_heredoc_delim(t_list *expressions)
{
	char	*res;
	bool	flag;
	int		i;

	flag = false;
	res = NULL;
	while (expressions->next)
	{
		i = 0;
		while (((t_args *)expressions->content)->args[i])
		{
			if (flag)
			{
				res = ft_strdup(((t_args *)expressions->content)->args[i]);
				return (res);
			}
			if (((t_args *)expressions->content)->state == HEREDOC)
				flag = true;
			i++;
		}
		expressions = expressions->next;
	}
	return (res);
}

char	*check_line(char *line, t_envs *envs)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = NULL;
	if (line[i] == '$' && ft_isalnum(line[i + 1]))
	{
		new_line = get_var(line, envs, check_for_vars(line, false));
		return (new_line);
	}
	return (line);
}

int	check_vars(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '$' && ft_isalnum(line[i + 1]))
		return (1);
	return (0);
}

int	do_heredoc(t_list *expressions, t_params *params, t_envs *envs, bool flag)
{
	char	*heredoc_line;
	char	*line;
	char	*delim;
	size_t	done;

	done = 0;
	delim = get_heredoc_delim(expressions);
	if (flag)
	{
		while (true)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &ft_here_sig);
			heredoc_line = readline("> ");
			line = ft_strjoin(heredoc_line, "\n");
			free(heredoc_line);
			done = heredoc_checker(line, delim);
			if (check_vars(line))
			{
				line = check_line(line, envs);
				line = ft_strjoin(line, "\n");
			}
			if (done)
				break ;
			if (ft_strcmp(((t_args *)expressions->content)->args[1], "<<") == 0)
				write(params->heredoc_fd, line, ft_strlen(line));
			if (line)
				free(line);
		}
		params->heredoc_fd = open(".heredoc.tmp", O_RDONLY | 0644);
		params->input_fd = params->heredoc_fd;
		free(delim);
		if (line)
			free(line);
	}
	return (0);
}
