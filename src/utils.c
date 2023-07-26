/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 01:10:30 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s || !(new_str = (char *)malloc(len + 1)))
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen((char *)s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*get_token(char *input)
{
	size_t	i = 0;
	char    *token;

	while (input[i])
	{
		if (input[i] == ' ')
		{
			token = ft_substr(input, 0, i);
			break ;
		}
		//ultima palavra
		else if (input[i + 1] == '\0')
		{
			token = ft_substr(input, 0, i + 1);
			break ;
		}
		i++;
	}
	return (token);
}

t_args *set_args_tokens(char *input, t_args *args)
{
	char *token;
	size_t j = 0;

	while (*input && *input == ' ')
		input++;
	while (*input)
	{
		token = get_token(input);
		if (!token)
			break;
		args->tokens[j] = token;
		input += ft_strlen(token);
		while (*input && *input == ' ')
			input++;
		j++;
	}
	args->tokens[j] = NULL; // Set the last element to NULL to mark the end
	return (args);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	check_builtin(t_args *args, t_pid *proccess)
{
	if (ft_strcmp(args->tokens[0], "exit") == 0)
		exit_function(args, proccess);
}

t_pid	*initialize_pid()
{
	t_pid	*proccess;

	proccess = malloc(sizeof(t_pid));
	proccess->pid = 0;
	return (proccess);
}

t_args	*initialize_args()
{
	t_args	*args = malloc(sizeof(t_args));
	int	i;

	i = 0;
	args->len = 0;
	while (i < MAX_ARGS)
		args->tokens[i++] = NULL;
	return (args);
}

char	*ft_strdup(char *s)
{
	int		len;
	int		i;
	char	*alloc;

	len = ft_strlen(s);
	i = 0;
	alloc = malloc(sizeof(char) * (len + 1));
	if (!alloc)
		return (NULL);
	while (i < len)
	{
		alloc[i] = s[i];
		++i;
	}
	alloc[i] = '\0';
	return (alloc);
}
