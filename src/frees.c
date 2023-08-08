/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:30:01 by jbranco-          #+#    #+#             */
/*   Updated: 2023/08/08 16:58:24 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envs(char **my_envs)
{
	int	i;

	i = 0;
	while (my_envs[i])
		free(my_envs[i++]);
	free(my_envs);
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