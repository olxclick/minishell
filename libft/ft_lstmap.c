/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:28:50 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/22 17:29:23 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new;
	t_list		*index_new;
	t_list		*index_old;

	new = ft_lstnew((*f)(lst->content));
	if (!lst || !new)
		return (NULL);
	index_new = new;
	index_old = lst->next;
	while (index_old)
	{
		index_new->next = ft_lstnew((*f)(index_old->content));
		if (!(index_new->next))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		index_new = index_new->next;
		index_old = index_old->next;
	}
	return (new);
}
