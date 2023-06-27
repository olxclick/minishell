/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/27 14:34:59 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	loop()
{
	char	*input;

	while (1)
	{
		input = readline("shell--> ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		add_history(input);
		if (process(input))
			break ;
	}
}

int	process(char *input)
{
	t_args	*args;
	size_t	i;

	i = 0;
	args = format_input(input);
	char	*path;
	path = getenv("PATH");
	if (path == NULL)
		printf("Unable to retrieve path");
	while (i < args->len)
	{
		char *dir = strtok(path, ":");
		while (dir != NULL)
		{
			char exec_path[MAX_PATH_LENGTH];
			strncpy(exec_path, dir, sizeof(exec_path));
			strncat(exec_path, "/", sizeof(exec_path) - strlen(exec_path) - 1);
			strncat(exec_path, args->expression[i], sizeof(exec_path) - strlen(exec_path) - 1);
			execve(exec_path, args->expression, NULL);
			dir = strtok(NULL, ":");
		}
		i++;
	}
	return (1);
}

int	main()
{
	loop();
	rl_clear_history();
	return (0);
}
