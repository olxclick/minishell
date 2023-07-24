/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/24 16:22:26 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_all(t_args *args)
{
	size_t	i;

	i = 0;
	while (i < args->len)
		free(args->expression[i++]);
	free(args);
	rl_clear_history();
}

int	main()
{
	loop();
	return (0);
}

void	loop()
{
	t_args	*args;
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
		args = format_input(input);
		if (args)
		{
			process(args);
			free_all(args);
		}
	}
}

char	*exec_cmd(t_args *args, size_t i, char *exec_path, char *dir)
{
	size_t len;

	len = sizeof(exec_path);
	snprintf(exec_path, len, "%s/%s", dir, args->expression[i]);
	execve(exec_path, args->expression, NULL);
	dir = strtok(NULL, ":");
	return (dir);
}

int	process(t_args *args)
{
	size_t i;
    char *path;
    
    i = 0;
    path = getenv("PATH");
    if (path == NULL) {
        printf("Unable to retrieve path\n");
        return 0;
    }
    
    while (i < args->len) 
    {
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Fork failed\n");
            return 0;
        } else if (pid == 0) {
            // Child process
            
            char exec_path[MAX_PATH_LENGTH];
            char *dir = strtok(path, ":");
            while (dir != NULL) {
		check_builtin(args);
                snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, args->expression[i]);
                execve(exec_path, args->expression, NULL);
                dir = strtok(NULL, ":");
            }
            
            // If execve fails, exit the child process
            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            
            // Check if child process terminated normally
            /*if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Child process exited with status: %d\n", exit_status);
            }*/
        }
        
        i++;
    }
    return 1;
}