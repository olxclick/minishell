/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:17:21 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/25 16:50:02 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen((char *)str) + 1;
	while (--i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&(str[i]));
	}
	return (NULL);
}
/*
int main()
{
	char *s = "miaua";
	char c = 'u';

	printf("%p\n", ft_strrchr(s, c));
}*/
