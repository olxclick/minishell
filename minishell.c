/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/28 15:59:19 by jbranco-         ###   ########.fr       */
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
}

int	main()
{
	loop();
	rl_clear_history();
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

int	process(t_args *args)
{
	size_t	i;
	char	*path;

	i = 0;
	path = getenv("PATH");
	if (path == NULL)
	{
		printf("Unable to retrieve path\n");
		return (0);
	}
	while (i < args->len)
	{
		char exec_path[MAX_PATH_LENGTH];
		char *dir = strtok(path, ":");

		while (dir != NULL)
		{
			snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, args->expression[i]);
			execve(exec_path, args->expression, NULL);
			dir = strtok(NULL, ":");
		}
		i++;
	}
	return (1);
}