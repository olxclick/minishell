/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/26 14:44:37 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	failed(char *command, char *message)
{
	printf("%s\n", message);
	free(command);
	return (0);
}

int	main(void)
{
    char *command;
    char *path;
    char *args[MAX_ARGS];

    while (1)
    {
        command = readline("shell> ");
        if (command == NULL)
            failed(command, "Value stored is NULL");
        if (strlen(command) == 0)
            continue;

        int i = 0;
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
		failed(command, "Unable to retrieve path");

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