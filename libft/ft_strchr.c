/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:45:05 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/21 16:47:32 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (!s[i])
			return (0);
		i++;
	}
	return ((char *)s + i);
}
/*
int main()
{
	char *s = "teste";
	char c = 'e';

	printf("%p\n", ft_strchr(s, c));
}*/
