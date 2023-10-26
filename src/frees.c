/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:30:01 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/26 17:18:58 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_free(t_envs *my_envs)
{
	int	i;

	i = 0;
	if (my_envs)
	{
		if (my_envs->vars)
		{
			while (i < my_envs->len)
			{
				if (my_envs->vars[i])
					free(my_envs->vars[i]);
				i++;
			}
			if (my_envs->oldpwd)
				free(my_envs->oldpwd);
			if (my_envs->pwd)
				free(my_envs->pwd);
			free(my_envs->vars);
		}
		free(my_envs);
	}
}

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
	free (expression->args);
	free (expression);
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
