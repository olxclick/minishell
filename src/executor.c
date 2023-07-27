/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:38 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 00:21:343:27 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_path(char **envs, char *to_find)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (ft_strncmp(envs[i], to_find, ft_strlen(to_find) - 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char *expr, char **envs)
{
	char		*full_path;
	char		*bin;
	char		**path_env;
	size_t		i;

	(void)expr;
	bin = NULL;
   	//verificar se existe PATH nas nossas envs
	if (search_path(envs, "PATH") != -1)
	{
		bin = ft_strjoin("/", expr);
		path_env = ft_split(envs[search_path(envs, "PATH")], ':');
		i = 0;
		while (path_env[i])
		{
			full_path = ft_strjoin(path_env[i], bin); //usr/local/bin/ls
			if (access(full_path, F_OK) == 0) //verificar se existe no atual full_path
			{
				free_envs(path_env);
				free(bin);
				return (full_path);
			}
			free(full_path);
			i++;
		}
		free_envs(path_env);
	}
	free(bin);
	return (NULL);
}

void	exec(t_args *expr, char **my_envs)
{
    	char    *path;

        // procura o caminho de N cmd que está na posicao 0
        path = get_path(expr->args[0], my_envs);
	/*Distinguir no futuro os nossos builtins dos que ja estao implementados*/
        expr->args[expr->len] = 0;
    	execve(path, expr->args, my_envs);
}

void    executor(t_list *expressions, char **envs, t_params params)
{
	t_args  *expr;
	//create the fd's
	pipe(params.pipe_fd);
	params.pid = fork();
	if (params.pid == 0)//child
	{
		expr = expressions->content;
		handle_pipes(expressions, params);
          	exec(expr, envs);
	}
	else //parent
	{
       		close(params.pipe_fd[W]);
		if (params.input_fd != STDIN_FILENO)
			close(params.input_fd);
		wait(NULL);
        	while (expressions->next)
		{
			expr = expressions->content;
			if (expr->state == PIPE)// ls | wc pipe_fd[1]
			{
				params.input_fd = params.pipe_fd[R];
				expressions = expressions->next;
				executor(expressions, envs, params);
				break ;
			}
			expressions = expressions->next;
		}
		close_file_descriptors(params);
	}
}
