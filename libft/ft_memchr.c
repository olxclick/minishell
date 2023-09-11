/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:29:42 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/24 14:49:13 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}
/*
int main()
{
	char *s = "miaua";
	char c = 'u';

	printf("%p\n", ft_memchr(s, c, 5));
}*/
