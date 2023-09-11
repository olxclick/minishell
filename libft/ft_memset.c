/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:23:16 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/21 15:12:15 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main()
{
	char	s[] = "olaaa";
	void	*p;
	void	*res;

	p = s;
	res = ft_memset(p, 'f', 3);
	printf("%s", (char *)res);	
}
*/
