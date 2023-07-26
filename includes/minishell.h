/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/26 17:51:43 by jbranco-         ###   ########.fr       */
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
# include "../libft/libft.h"

#define MAX_ARGS 64
#define MAX_PATH_LENGTH 1024

typedef enum
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	DOC, //FILE
	DEFAULT
}	t_state;

typedef struct s_args
{
	char	**args;
	t_state	state;
	size_t	len;
}			t_args;

typedef struct s_token
{
	char	**token;
}			t_token;

typedef struct s_pid
{
	pid_t	pid;
}			t_pid;

int	process(t_args *args, t_pid *proccess);
void	loop();
void	free_all(t_args *args, t_pid *proccess);
void	exit_function(t_args *args, t_pid *proccess);
void	check_builtin(t_args *args, t_pid *proccess);
t_args	*format_input(t_args *args, char *input);
t_token set_args_tokens(char *input);
t_args    *get_parsed(t_token t);
char	*get_token(char *input);
char	*operator_return(char *token, char *input, int i);
t_list    *get_all_tokens(t_token t);
char **get_args(t_token t, int end);
static inline int is_delim(char *token)
{
    return (ft_strcmp(token, "|") || ft_strcmp(token, "<") || ft_strcmp(token, ">")
        || ft_strcmp(token, "<<") || ft_strcmp(token, ">>"));
}
t_state	get_state(t_args *args, t_state prev_state);
t_state	get_delim(char *token);

#endif