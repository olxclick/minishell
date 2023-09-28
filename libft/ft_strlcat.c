/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasferre <vasferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:40:21 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/28 17:04:48 by vasferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	i = 0;
	j = 0;
	if (!src && !dst)
		return (0);
	if (size == 0)
		return (ft_strlen((char *)src));
	while (dst[j] != '\0')
	{
		j++;
	}
	dlen = j;
	slen = ft_strlen(src);
	if (size == 0 || size <= dlen)
		return (slen + size);
	while (src[i] != '\0' && i < size - dlen - 1)
		dst[j++] = src[i++];
	if (src[0] != '\0')
		dst[j] = '\0';
	return (dlen + slen);
}
/*
int main (void)
{
	char src[] = "cyka Blyeat";
    	char dst [] = "1337 42690";
    	printf("%li \n", ft_strlcat(dst, src, 20));
    	printf("%s \n", dst);
}*/
