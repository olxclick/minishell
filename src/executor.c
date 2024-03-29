/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:38 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/15 13:09:12 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(t_list *expressions, t_envs *envs, t_params *params,
		bool flag)
{
	if (redir_needed(expressions) == 1 && flag)
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
	t_list	*original;

	original = expressions;
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
	if (flag)
		run_parent(expressions, params, envs, true);
	waitpid(-1, &g_exit, 0);
	run_parent(original, params, envs, false);
	if (!WTERMSIG(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	close_file_descriptors(params);
}
