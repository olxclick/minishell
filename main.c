/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/26 17:33:19 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	loop(char **env)
{
	char	*input;

	while (1)
	{
		set_pid();
		input = readline("shell--> ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		add_history(input);
		if (process(env, input))
			break ;
	}
}

int	process(char **env, char *input)
{
	t_args	args;

	//fazer funcao para separar o input em tokens conforme (" ", "|", "<>")
	char	*path;
	path = getenv("PATH");
	if (path == NULL)
		printf("Unable to retrieve path");
	char *dir = strtok(path, ":");
	while (dir != NULL)
	{
		char exec_path[MAX_PATH_LENGTH];
		strncpy(exec_path, dir, sizeof(exec_path));
		strncat(exec_path, "/", sizeof(exec_path) - strlen(exec_path) - 1);
		strncat(exec_path, args[0], sizeof(exec_path) - strlen(exec_path) - 1);
		execve(exec_path, args, NULL);
		dir = strtok(NULL, ":");
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	loop(env);
	rl_clear_history();
	return (0);
}