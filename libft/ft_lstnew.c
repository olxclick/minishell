/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:41:07 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/22 15:50:28 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int main()
{
	printf("%s", (char *)ft_lstnew("mimimi"));
}*/
