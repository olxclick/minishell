/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:30:01 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/29 17:02:13 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_free(t_envs *my_envs)
{
	int	i;

	i = 0;
	while (i < my_envs->len)
		free(my_envs->vars[i++]);
	free(my_envs->oldpwd);
	free(my_envs->vars);
	free(my_envs);
}

void	free_token(char **my_envs)
{
	int	i;

	i = 0;
	while (i < get_envs_size(my_envs))
		free(my_envs[i++]);
	if (my_envs)
		free(my_envs);
}

void	cd_free(char *value, char *buffer, t_envs *my_envs)
{
	free(value);
	free(buffer);
	free(my_envs->buf);
}

void	free_args(t_args *expression) {
	if (expression == NULL)
		return;

	for (size_t i = 0; expression->args[i]; i++) {
		free(expression->args[i]);
	}
	free(expression->args);
	free(expression);
}

void free_list(t_list *head) {
	t_list *current = head;
	t_list *next;

	while (current != NULL) {
		next = current->next;
		free_args(current->content);
		free(current);
		current = next;
	}
}