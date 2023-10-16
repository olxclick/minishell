/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:30:11 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/16 15:21:36 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_exit;
char	**global_envs;
char	**global_args;

t_params	init_params(t_list *expressions)
{
	t_params	params;

	params.input_fd = STDIN_FILENO;
	params.output_fd = STDOUT_FILENO;
	params.heredoc_fd = open(".heredoc.tmp", O_CREAT
			| O_TRUNC | O_RDWR, 0644);
	params.exited = 0;
	params.exit_flag = 0;
	params.exit_status = 130;
	params.files = create_files(expressions);
	return (params);
}

t_envs	*init_envs(t_envs *my_envs, char **envs)
{
	my_envs->vars = set_envs(envs);
	my_envs->len = get_envs_size(envs);
	my_envs->buf = NULL;
	my_envs->oldpwd = NULL;
	return (my_envs);
}

size_t	process(char *input, t_envs *envs)
{
	size_t		has_finished;
	t_list		*expressions;
	t_token		tokens;
	t_params	params;

	tokens = set_args_tokens(input, envs);
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
	unlink(".heredoc.tmp");
	close(params.heredoc_fd);
	return (has_finished);
}

void	loop(t_envs *my_envs)
{
	char	*input;

	while (true)
	{
		signals(1);
		input = readline("shell--> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (process(input, my_envs))
			break ;
	}
}
int	main(int argc, char **argv, char **envs)
{
	t_envs	*my_envs;

	(void)argc;
	(void)argv;
	global_args = argv;
	global_envs = envs;
	my_envs = malloc(sizeof(t_envs));
	my_envs = init_envs(my_envs, envs);
	loop(my_envs);
	copy_free(my_envs);
	rl_clear_history();
	return (g_exit);
}

void	print_list(t_list *expressions)
{
	int	i;

	while (expressions->next)
	{
		i = 0;
		while (((t_args *)expressions->content)->args[i])
			printf("Token: %s\n", ((t_args *)expressions->content)->args[i++]);
		printf("State: %d\n", ((t_args *)expressions->content)->state);
		expressions = expressions->next;
	}
}
