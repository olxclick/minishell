/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:38 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/30 18:00:46 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_path(char *path)
{
	char	*new_path;
	int		i;

	i = 0;
	while (path[i] != '/')
		i++;
	new_path = ft_substr(path, i, ft_strlen(path));
	free(path);
	return (new_path);
}

char	*define_path(t_envs *envs, char *expr)
{
	char		*full_path;
	char		*bin;
	char		**path_env;
	size_t		i;

	i = 0;
	bin = ft_strjoin("/", expr);
	path_env = ft_split(envs->vars[pos_env_var(envs, "PATH")], ':');
	i = 0;
	while (path_env[i])
	{
		full_path = ft_strjoin(path_env[i], bin);
		if (full_path[0] != '/')
			full_path = check_path(full_path);
		if (access(full_path, F_OK) == 0)
		{
			free_token(path_env);
			free(bin);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_token(path_env);
	free(bin);
	return (NULL);
}

char	*get_path(char *expr, t_envs *envs)
{
	if (expr[0] == '/' || ft_strncmp(expr, "./", 2) == 0)
		return (expr);
	if (pos_env_var(envs, "PATH") != -1)
		return (define_path(envs, expr));
	return (NULL);
}

int	exec(t_list *expressions, t_args *expr, t_envs *my_envs, char *path)
{
	free(expr->args[expr->len]);
	expr->args[expr->len] = NULL;
	if (is_child_builtin(expr->args[0])
		|| (ft_strcmp(expr->args[0], "export") == 0 && expr->len == 1))
		g_exit = exec_child_builtin(expressions, expr, my_envs);
	else
		execve(path, expr->args, my_envs->vars);
	return (g_exit);
}

int	child_process(t_list *expressions, t_envs *envs, t_params *params)
{
	t_args	*expr;
	char	*path;

	expr = expressions->content;
	if (redir_needed(expressions) == 1)
	{
		redir_input(expressions, params);
		redirect(params);
	}
	else if (redir_needed(expressions) == 2)
	{
		params->heredoc_fd = open(".heredoc.tmp", O_CREAT
				| O_TRUNC | O_RDWR, 0644);
		do_heredoc(expressions, params, envs);
	}
	path = get_path(expr->args[0], envs);
	if (is_child_builtin(expr->args[0]) || path
		|| ((ft_strcmp(expr->args[0], "export") == 0 && expr->len == 1)))
	{
		handle_pipes(expressions, params);
		if ((redir_needed(expressions) == 2 && ft_lstsize(expressions) <= 4)
			|| redir_needed(expressions) != 2)
			g_exit = exec(expressions, expr, envs, path);
	}
	else if (!is_parent_builtin(expr->args[0], expr->len))
	{
		printf("%s: command not found\n", expr->args[0]);
		g_exit = 127;
	}
	else
		g_exit = 1;
	free(path);
	return (g_exit);
}

int	run_parent(t_list *expressions, t_params *params,
	t_envs *envs, t_args *expr)
{
	close(params->pipe_fd[W]);
	if (params->input_fd != STDIN_FILENO)
		close(params->input_fd);
	if ((is_parent_builtin(expr->args[0], expr->len)))
		g_exit = exec_parent_builtin(expressions, expr, params, envs);
	while (expressions->next)
	{
		expr = expressions->content;
		if (expr->state == PIPE)
		{
			params->input_fd = params->pipe_fd[R];
			expressions = expressions->next;
			executor(expressions, envs, params);
			break ;
		}
		else if (expr->state == REDIR_OUT || expr->state == REDIR_APPEND)
		{
			waitpid(params->pid, NULL, 0);
			if (open(".heredoc.tmp", O_RDONLY | 0644) == -1)
				params->input_fd = params->pipe_fd[R];
			else
				params->input_fd = open(".heredoc.tmp", O_RDONLY | 0644);
			do_redir_out(params);
		}
		expressions = expressions->next;
	}
	return (g_exit);
}

void	executor(t_list *expressions, t_envs *envs, t_params *params)
{
	t_args	*expr;
	t_list	*original;

	original = expressions;
	expr = expressions->content;
	pipe(params->pipe_fd);
	params->pid = fork();
	signals(2);
	if (envs->pwd)
		free(envs->pwd);
	envs->pwd = getcwd(envs->buf, PATH_MAX);
	if (params->pid == 0)
	{
		g_exit = child_process(expressions, envs, params);
		exit(g_exit);
	}
	run_parent(expressions, params, envs, expr);
	waitpid(-1, &g_exit, 0);
	// run_parent(original, params, envs, expr);
	if (!WTERMSIG(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	close_file_descriptors(params);
}
