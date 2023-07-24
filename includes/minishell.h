/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/05 17:37:29 by pedda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdint.h>

#define MAX_ARGS 64
#define MAX_PATH_LENGTH 1024

typedef struct s_args
{
	char	*expression[MAX_ARGS];
	size_t	len;
}			t_args;

int	process(t_args*args);
void	loop();
t_args	*format_input(char *input);
t_args	*initialize_args();
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);

#endif