/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:03:59 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/21 17:04:30 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little && len == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (!little[++j])
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	char big[] = "student42penicheschool";
	char small[] = "peniche";

	printf("%s", ft_strnstr(big, small, 18));
}
*/
