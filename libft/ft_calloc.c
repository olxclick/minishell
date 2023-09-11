/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:50:42 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/15 13:24:38 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc (nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
/*
int	main()
{
	printf ("%p", (char *)ft_calloc(412, 41));
}*/
