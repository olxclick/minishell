/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 00:25:50 by jbranco-         ###   ########.fr       */
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

typedef enum
{
	CMD,
	PIPE
}	t_state;

typedef struct s_args
{
	char	*tokens[MAX_ARGS];
	size_t	len;
}			t_args;

typedef struct s_pid
{
	pid_t	pid;
}			t_pid;

int	process(t_args *args, t_pid *proccess);
void	loop(t_args *args, t_pid *proccess);
void	free_all(t_args *args, t_pid *proccess);
void	exit_function(t_args *args, t_pid *proccess);
void	check_builtin(t_args *args, t_pid *proccess);
t_args	*format_input(t_args *args, char *input);
t_pid	*initialize_pid();
int	ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_args	*initialize_args();
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(char *str);
t_args	*set_args_tokens(char *input, t_args *args);
char	*get_token(char *input);
char	*ft_strdup(char *s);

#endif