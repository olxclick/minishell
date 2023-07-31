
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

t_params	init_params()
{
	t_params params;
	
	params.input_fd = STDIN_FILENO;
	params.output_fd = STDOUT_FILENO;
	params.exited = 0;
	return (params);
}

int	main(int argc, char **argv, char **envs)
{
	(void)argc;
	(void)argv;
	char	**my_envs;

	my_envs = set_envs(envs);
	loop(my_envs);
	rl_clear_history();
	return (0);
}

size_t	process(char *input, char **envs)
{
	size_t	has_finished;
	t_list	*expressions;
	t_token	tokens;
	t_params	params;

	tokens = set_args_tokens(input);
	expressions = get_all_tokens(tokens);
	params = init_params();
	executor(expressions, envs, &params);
	printf("exited: %ld\n", params.exited);
	has_finished = params.exited;
	free_envs(tokens.token);
	free_list(expressions);
	free(input);
	return (has_finished);
}

void	loop(char **my_envs)
{
	char	*input;

	while (true)
	{
		input = readline("shell--> ");
		if (!ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (process(input, my_envs))
			break ;
	}
	free_envs(my_envs);
	rl_clear_history();
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