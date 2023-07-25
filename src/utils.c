/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/25 22:31:35 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_mid_token(t_args *args, char *full_token, size_t j, size_t k)
{
	if (full_token[j] == '|')
	{	
		args->expression[k] = malloc(2);
		args->expression[k][0] = '|';
		args->expression[k][1] = '\0';
	}
	else if (full_token[j] == '>')
	{
		args->expression[k] = malloc(2);
		args->expression[k][0] = '>';
		args->expression[k][1] = '\0';
	}
	else if (full_token[j] == '<')
	{
		args->expression[k] = malloc(2);
		args->expression[k][0] = '<';
		args->expression[k][1] = '\0';
	}
}

size_t		skip_spaces(char *full_token, size_t j, bool pipe)
{
	size_t	i;

	i = 0;
	if (pipe == true)
	{
		while (full_token[j] == ' ')
		{
			i++;
			j++;
		}
	}
	else
	{
		j--;
		while (full_token[j] == ' ')
		{
			j--;
			i++;
		}
	}
	return (i);
}

t_args	*format_input(t_args *args, char *input)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	spaces;
	bool	pipe;
	char	*full_token;

	k = 0;
	i = 0;
	j = 0;
	pipe = false;
	full_token = malloc((ft_strlen(input) + 1) * sizeof(char));
	ft_strlcpy(full_token, input, ft_strlen(input) + 1);
	if (full_token[i])
	{
		while (full_token[i])
		{
			if (pipe == true)
			{
				spaces = skip_spaces(full_token, j, pipe);
				i += spaces;
				spaces = skip_spaces(full_token, j, pipe);
				j += spaces;
				pipe = false;
			}
			while ((full_token[j]) && full_token[j] != '|' && full_token[j] != '>' && full_token[j] != '<')
				j++;
			spaces = skip_spaces(full_token, j, pipe);
			if (j > i)
			{
				if (args->expression[k])
					free(args->expression[k]);
				args->expression[k] = malloc(sizeof(char) * (j - i - spaces) + 1);
				ft_strlcpy(args->expression[k], &full_token[i], (j - i - spaces) + 1);
				k++;
				args->len++;
			}
			if (full_token[j] == '|' || full_token[j] == '>' || full_token[j] == '<')
			{
				check_mid_token(args, full_token, j, k);
				k++;
				args->len++;
				j++;
				pipe = true;
			}
			i = j;
		}
		free(full_token);
	}
	i = 0;
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
	if (ft_strcmp(args->expression[0], "exit") == 0)
		exit_function(args, proccess);
}

t_pid	*initialize_pid()
{
	t_pid	*proccess;

	proccess = malloc(sizeof(t_pid));
	proccess->pid = 0;
	proccess->state = 0;
	return (proccess);
}

t_args	*initialize_args()
{
	t_args	*args = malloc(sizeof(t_args));
	int	i;

	i = 0;
	args->len = 0;
	while (i < MAX_ARGS)
		args->expression[i++] = NULL;
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
