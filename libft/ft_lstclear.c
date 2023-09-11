/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:05:16 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/22 17:14:15 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;

	if (!lst)
		return (0);
	while (*lst != NULL)
	{
		new = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = new;
	}
	return (0);
}
