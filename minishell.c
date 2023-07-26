/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 00:43:07 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_all(t_args *args, t_pid *proccess)
{
	size_t	i;

	i = 0;
	if (args)
	{
		while (i < args->len)
			free(args->tokens[i++]);
		free(args);
	}
	if (proccess)
		free(proccess);
	rl_clear_history();
}

int	main()
{
	t_args	*args;
	t_pid	*proccess;

	proccess = initialize_pid();
	args = initialize_args();
	loop(args, proccess);
	return (0);
}

void	loop(t_args *args, t_pid *proccess)
{
	static char	*input;
	(void)proccess;
	while (1)
	{
		input = readline("shell--> ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break;
		}
		add_history(input);
		args = set_args_tokens(input, args);
		/*
		if (args)
			if (!process(args, proccess))
				break ;
		*/
	}
}

int	process(t_args *args, t_pid *proccess)
{
	size_t i;
    	char *path;

   	i = 0;
   	path = getenv("PATH");
	if (path == NULL) {
		printf("Unable to retrieve path\n");
		return (0);
	}
	while (i < args->len) 
	{
		int pipe_fd[2];
		pipe(pipe_fd);//fd0 = read fd1 =write
		//comunicar com o pai
		proccess->pid = fork();
		if (proccess->pid < 0)
		{
			printf("Fork failed\n");
			return (0);
		}
		else if (proccess->pid == 0) //child
		{
			char exec_path[MAX_PATH_LENGTH];
			char *dir = strtok(path, ":");
			while (dir != NULL)
			{
				check_builtin(args, proccess);
				snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, args->tokens[i]);
				execve(exec_path, args->tokens, NULL);
				dir = strtok(NULL, ":");
			}
			free_all(args, proccess);
			exit(1);
		}
		else //parent
		{
			int status;
			waitpid(proccess->pid, &status, 0);
			//caso pipe
			//ls | wc
			//CMD PIPE CMD
		}
		i++;
	}
	return (1);
}