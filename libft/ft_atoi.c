/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:38:55 by jbranco-          #+#    #+#             */
/*   Updated: 2022/11/21 17:14:56 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_white_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	atoi;

	i = ft_check_white_spaces((char *)str);
	atoi = 0;
	signal = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = signal * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = atoi * 10 + str[i] - 48;
		i++;
	}
	return (atoi * signal);
}
/*
int main()
{
	int val;
	char strn1[] = "12546";
	
	val = atoi(strn1);
	printf("String value = %s\n", strn1);
	printf("Integer value = %d\n", val);

	char strn2[] = "GeeksforGeeks";
	val = atoi(strn2);
	printf("String value = %s\n", strn2);
	printf("Integer value = %d\n", val);
}
*/
