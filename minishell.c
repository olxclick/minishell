
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

t_params	init_params(t_params params)
{
	params.input_fd = STDIN_FILENO;
	params.output_fd = STDOUT_FILENO;
	return (params);
}

int	main(int argc, char **argv, char **envs)
{
	(void)argc;
	(void)argv;
	char	**my_envs;

	my_envs = set_envs(envs);
	loop(my_envs);
	return (0);
}

void	loop(char **my_envs)
{
	t_list	*expressions;
	t_token	token;
	t_params	params;
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
		expressions = get_all_tokens(token);
		params = init_params(params);
		executor(expressions, my_envs, params);
		// print_list(expressions);
	}
}

void	print_list(t_list *expressions)
{
	while (expressions->next)
	{
		int i = 0;
		while (((t_args *)expressions->content)->args[i])
			printf("Token: %s\n", ((t_args *)expressions->content)->args[i++]);
		printf("State: %d\n", ((t_args *)expressions->content)->state);
		expressions = expressions->next;
	}
}