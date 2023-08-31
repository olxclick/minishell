
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

t_params	init_params(t_list *expressions)
{
	t_params params;
	
	params.input_fd = STDIN_FILENO;
	params.output_fd = STDOUT_FILENO;
	params.exited = 0;
	params.exit_status = 0;
	params.files = create_files(expressions);
	return (params);
}

t_envs	*init_envs(t_envs *my_envs, char **envs)
{
	my_envs->vars = set_envs(envs);
	my_envs->len = get_envs_size(envs);
	return (my_envs);
}

size_t	process(char *input, t_envs *envs)
{
	size_t	has_finished;
	t_list	*expressions;
	t_token	tokens;
	t_params	params;

	tokens = set_args_tokens(input);
	expressions = get_all_tokens(tokens);
	if (!expressions)
	{
		free_token(tokens.token);
		free_list(expressions);
		free(input);
		return (0);
	}
	params = init_params(expressions);
	executor(expressions, envs, &params);
	has_finished = params.exited;
	free_token(tokens.token);
	free(params.files);
	free_list(expressions);
	free(input);
	return (has_finished);
}

void	loop(t_envs *my_envs)
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
	rl_clear_history();
}

int	main(int argc, char **argv, char **envs)
{
	(void)argc;
	(void)argv;
	t_envs	*my_envs;

	my_envs = malloc(sizeof(t_envs));
	my_envs = init_envs(my_envs, envs);
	loop(my_envs);
	copy_free(my_envs);
	rl_clear_history();
	return (0);
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
