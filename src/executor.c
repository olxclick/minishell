/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:38 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/09 23:24:15 by jbranco-         ###   ########.fr       */
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
	char	*full_path;
	char	*bin;
	char	**path_env;
	size_t	i;

	i = 0;
	bin = ft_strjoin("/", expr);
	path_env = ft_split(envs->vars[pos_env_var(envs, "PATH")], ':');
	i = -1;
	while (path_env[++i])
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
	}
	free_token(path_env);
	free(bin);
	return (NULL);
}

char	*get_path(char *expr, t_envs *envs)
{
	struct stat	buf;

	if (expr[0] == '/' || ft_strncmp(expr, "./", 2) == 0)
	{
		if (access(expr, F_OK) == 0)
		{
			if (stat(expr, &buf) == 0 && expr[0] == '/')
			{
				if (S_ISREG(buf.st_mode))
					return (expr);
			}
		}
		return (NULL);
	}
	if (pos_env_var(envs, "PATH") != -1)
		return (define_path(envs, expr));
	return (NULL);
}

int	exec(t_list *expressions, t_envs *my_envs, char *path,
		bool flag)
{
	t_args	*expr;

	expr = expressions->content;
	free(expr->args[expr->len]);
	expr->args[expr->len] = NULL;
	if (is_child_builtin(expr->args[0]) || (ft_strcmp(expr->args[0],
				"export") == 0 && expr->len == 1))
		g_exit = exec_child_builtin(expressions, expr, my_envs, flag);
	else if (flag)
		execve(path, expr->args, my_envs->vars);
	return (g_exit);
}

void	built_in_exec(t_list *expressions, t_envs *envs,
	t_params *params, bool flag)
{
	t_args	*expr;
	char	*path;

	expr = expressions->content;
	path = get_path(expr->args[0], envs);
	if (is_child_builtin(expr->args[0]) || path || ((ft_strcmp(expr->args[0],
					"export") == 0 && expr->len == 1)))
	{
		if (flag)
			handle_pipes(expressions, params);
		if ((redir_needed(expressions) == 2 && ft_lstsize(expressions) <= 4)
			|| redir_needed(expressions) != 2)
				g_exit = exec(expressions, envs, path, flag);
	}
	else if (!is_parent_builtin(expr->args[0], expr->len))
	{
		if (flag)
			printf("%s: command not found\n", expr->args[0]);
		g_exit = 127;
	}
	free(path);
}

int	child_process(t_list *expressions, t_envs *envs, t_params *params,
		bool flag)
{
	if (redir_needed(expressions) == 1)
	{
		redir_input(expressions, params, flag);
		redirect(params, flag);
	}
	else if (redir_needed(expressions) == 2)
		do_heredoc(expressions, params, envs, flag);
	built_in_exec(expressions, envs, params, flag);
	return (g_exit);
}

void	redir_parent(t_args *expr, t_params *params,
	t_list *original, bool flag)
{
	if ((expr->state == REDIR_OUT || expr->state == REDIR_APPEND) && flag)
	{
		waitpid(params->pid, NULL, 0);
		if (redir_needed(original) == 2)
			params->input_fd = open(".heredoc.tmp", O_RDONLY | 0644);
		do_redir_out(params);
	}
}

int	run_parent(t_list *expressions, t_params *params, t_envs *envs, bool flag)
{
	t_args	*expr;
	t_list	*original;

	original = expressions;
	expr = expressions->content;
	close(params->pipe_fd[W]);
	if (params->input_fd != STDIN_FILENO)
		close(params->input_fd);
	if ((is_parent_builtin(expr->args[0], expr->len)))
		g_exit = exec_parent_builtin(expressions, params, envs, flag);
	while (expressions->next)
	{
		expr = expressions->content;
		params->input_fd = params->pipe_fd[R];
		if (expr->state == PIPE)
		{
			expressions = expressions->next;
			executor(expressions, envs, params, flag);
			break ;
		}
		redir_parent(expr, params, original, flag);
		expressions = expressions->next;
	}
	return (g_exit);
}

void	executor(t_list *expressions, t_envs *envs, t_params *params, bool flag)
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
		g_exit = child_process(expressions, envs, params, flag);
		exit(g_exit);
	}
	run_parent(expressions, params, envs, true);
	waitpid(-1, &g_exit, 0);
	if (ft_strcmp(expr->args[0], "cat") != 0)
		run_parent(original, params, envs, false);
	if (!WTERMSIG(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	close_file_descriptors(params);
}
