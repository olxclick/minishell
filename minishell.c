
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 14:22:30 by jbranco-         ###   ########.fr       */
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
			free(args->args[i++]);
		free(args);
	}
	if (proccess)
		free(proccess);
	rl_clear_history();
}

int	main()
{
	loop();
	return (0);
}

void	loop()
{
	// t_list	*expressions;
	t_token	token;
	char	*input;
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
		token = set_args_tokens(input);
		printf("%s\n", token.token[0]);
		printf("%s\n", token.token[1]);
		printf("%s\n", token.token[2]);
		// expressions = get_all_tokens(token);
		// while (expressions)
		// {
		// 	for (int i = 0; ((t_args *)expressions->content)->args[i]; i++)
		// 		printf("Token: %s\n", ((t_args *)expressions->content)->args[i]);
		// 	printf("State: %d\n", ((t_args *)expressions->content)->state);
		// 	expressions = expressions->next;
		// }
		/*
		if (args)
			if (!process(args, proccess))
				break ;
		*/
	}
}

/*
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
*/