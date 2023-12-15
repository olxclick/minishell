/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:52:03 by jbranco-          #+#    #+#             */
/*   Updated: 2023/12/15 13:09:22 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
