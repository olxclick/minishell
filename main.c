/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/26 13:48:26 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
    char *command;
    char *path;
    char *args[MAX_ARGS];

    while (1)
    {
        command = readline("shell> ");
        if (command == NULL)
            break;

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
        {
            fprintf(stderr, "Unable to get the value of the PATH variable\n");
            break;
        }

        char exec_path[MAX_PATH_LENGTH];
        strcpy(exec_path, path);
        strcat(exec_path, "/");
        strcat(exec_path, args[0]);

        // Execute the command
        execve(exec_path, args, NULL);

        // execve failed, print error
        perror("execve");
        break;
    }

    free(command);
    return 0;
}