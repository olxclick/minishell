/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/26 16:34:22 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	loop(char *env)
// {
// 	char	*input;

// 	while (true)
// 	{
// 		set_pid();
// 		input = readline("shell--> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			free(input);
// 			break ;
// 		}
// 		else if (ft_is_all_whitespace(input))
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		add_history(input);
// 		if (process(env, input))
// 			break ;
// 	}
// }

int	main(void)
{
	// (void)argc;
	// (void)argv;
	char *command;
	char *path;
	char *args[MAX_ARGS];

	while (1)
	{
		int i = 0;
		command = readline("shell> ");
		// if (command == NULL)
		// 	failed(command, "Value stored is NULL");
		if (strlen(command) == 0)
			continue;
		char *token = strtok(command, " \t\r\n");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " \t\r\n");
		}
		args[i] = NULL;
		path = getenv("PATH");
		if (path == NULL)
			printf("Unable to retrieve path");
		// Search for the executable in the directories specified by PATH
		char *dir = strtok(path, ":");
		while (dir != NULL)
		{
			char exec_path[MAX_PATH_LENGTH];
			strncpy(exec_path, dir, sizeof(exec_path));
			strncat(exec_path, "/", sizeof(exec_path) - strlen(exec_path) - 1);
			strncat(exec_path, args[0], sizeof(exec_path) - strlen(exec_path) - 1);
			// Execute the command
			execve(exec_path, args, NULL);
			dir = strtok(NULL, ":");
		}
		fprintf(stderr, "Command not found: %s\n", args[0]);
	}
	free(command);
	return (0);
}
