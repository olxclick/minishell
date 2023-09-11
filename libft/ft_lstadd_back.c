/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:31:48 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/22 16:54:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tou;

	if (!lst)
		return ;
	if (*lst)
	{
		tou = ft_lstlast(*lst);
		tou->next = new;
	}
	else
		*lst = new;
}
