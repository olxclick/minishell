/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasferre <vasferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:38 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/05 15:17:16 by vasferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *expr, t_envs *envs)
{
	char		*full_path;
	char		*bin;
	char		**path_env;
	size_t		i;

	bin = NULL;
	if (pos_env_var(envs, "PATH") != -1)
	{
		bin = ft_strjoin("/", expr);
		path_env = ft_split(envs->vars[pos_env_var(envs, "PATH")], ':');
		i = 0;
		while (path_env[i])
		{
			full_path = ft_strjoin(path_env[i], bin);
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
	}
	free(bin);
	if (!is_parent_builtin(expr))
	{
		g_exit = 127;
		printf("%s: command not found\n", expr);
	}
	return (NULL);
}

void	exec(t_args *expr, t_envs *my_envs)
{
	char	*path;

	path = get_path(expr->args[0], my_envs);
	expr->args[expr->len] = 0;
	execve(path, expr->args, my_envs->vars);
}

int	child_process(t_list *expressions, t_envs *envs, t_params *params)
{
	t_args	*expr;

	expr = expressions->content;
	if (redir_needed(expressions) == 1)
	{
		redir_input(expressions, params);
		redirect(params);
	}
	else if (redir_needed(expressions) == 2)
		do_heredoc(expressions, params);
	handle_pipes(expressions, params);
	if (!is_child_builtin(expr->args[0]))
		exec(expr, envs);
	else
		g_exit = exec_child_builtin(expr, params);
	return (g_exit);
}

void	run_parent(t_list *expressions, t_params *params,
	t_envs *envs, t_args *expr)
{
	while (expressions->next)
	{
		close(params->pipe_fd[W]);
		if (params->input_fd != STDIN_FILENO)
			close(params->input_fd);
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
			params->input_fd = params->pipe_fd[R];
			do_redir_out(params);
		}
		expressions = expressions->next;
	}
	if (is_parent_builtin(expr->args[0]))
		exec_parent_builtin(expr, params, envs);
}

void	executor(t_list *expressions, t_envs *envs, t_params *params)
{
	t_args	*expr;

	pipe(params->pipe_fd);
	expr = expressions->content;
	params->pid = fork();
	signals(2);
	signal(SIGQUIT, SIG_IGN);
	if (params->pid == 0)
		exit(g_exit = child_process(expressions, envs, params));
	else
	{
		waitpid(params->pid, &g_exit, 0);
		if (!WTERMSIG(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		close(params->pipe_fd[W]);
		if (params->input_fd != STDIN_FILENO)
			close(params->input_fd);
		run_parent(expressions, params, envs, expr);
		close_file_descriptors(params);
	}
}
