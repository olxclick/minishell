#include "includes/minishell.h"

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
		new_line = get_var(line, envs);
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

void	define_file(t_args *expr, int *files, t_state prev_state)
{
	if (prev_state == REDIR_OUT)
		*files = open(expr->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*files = open(expr->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
}
