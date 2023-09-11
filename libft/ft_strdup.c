/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:02:45 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/21 15:59:30 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen((char *)src);
	new = (char *) malloc(size * sizeof(char) + 1);
	if (new != 0)
	{
		while (src[i] != '\0')
		{
			new[i] = src[i];
			i++;
		}	
	}
	else
	{
		return (0);
	}
	new[i] = '\0';
	return (new);
}
/*int main()
{
	printf("%s", ft_strdup("adshfgfag"));
}*/
