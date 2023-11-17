/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:47:57 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/17 11:48:03 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    inicializa certos valores para os devidos
    parametros que vao ser utlilizados pelo
    programa
*/
t_params	init_params(t_list *expressions)
{
	t_params	params;

	params.input_fd = STDIN_FILENO;
	params.exited = 0;
	params.heredoc_fd = open(".heredoc.tmp", O_CREAT | O_TRUNC | O_RDWR,
			0644);
	params.exit_flag = 0;
	params.exit_status = 130;
	params.files = create_files(expressions);
	return (params);
}

/*
    inicializa a estrotura t_envs com os devidos 
    valores dados as variaveis ambientais
*/
t_envs	*init_envs(t_envs *my_envs, char **envs)
{
	my_envs->vars = set_envs(envs);
	my_envs->len = get_envs_size(envs);
	my_envs->buf = NULL;
	my_envs->oldpwd = NULL;
	my_envs->pwd = getcwd(my_envs->buf, PATH_MAX);
	return (my_envs);
}
