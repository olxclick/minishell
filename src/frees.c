/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:30:01 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/14 12:02:04 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(char **my_envs)
{
	int	i;

	i = 0;
	if (!my_envs || !my_envs[0])
		return ;
	while (i < get_envs_size(my_envs))
	{
		free(my_envs[i++]);
	}
	if (my_envs)
		free(my_envs);
}

void	cd_free(char *value, t_envs *my_envs)
{
	free(value);
	free(my_envs->buf);
}

void	free_args(t_args *expression)
{
	size_t	i;

	i = 0;
	if (expression == NULL)
		return ;
	while (expression->args[i])
	{
		free(expression->args[i]);
		i++;
	}
	free(expression->args);
	free(expression);
}

void	free_buf(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_args(current->content);
		free(current);
		current = next;
	}
}
