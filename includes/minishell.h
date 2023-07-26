/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/27 00:25:58 by jbranco-         ###   ########.fr       */
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
# include <string.h>
# include <sys/types.h>
# include <stdint.h>
# include "../libft/libft.h"

#define W 1 //write fd
#define R 0 //read fd

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

typedef struct s_params
{
	int	pipe_fd[2];
	int	input_fd;
	int	output_fd;
	pid_t	pid;
}			t_params;

typedef struct s_token
{
	char	**token;
}			t_token;

void	loop(char **my_envs);
void	free_all(t_args *args);
char	*get_path(char *expr, char **envs);
int	search_path(char **envs, char *to_find);
t_token set_args_tokens(char *input);
void	exec(t_args *expr, char **my_envs);
void    executor(t_list *expressions, char **envs, t_params params);
t_args    *get_parsed(t_token t);
char	*get_token(char *input);
char	*operator_return(char *token, char *input, int i);
t_list    *get_all_tokens(t_token t);
char **get_args(t_token t, int end);
void	handle_pipes(t_list *expressions, t_params parameters);
t_state	get_state(t_args *args, t_state prev_state);
void print_list(t_list *head);
t_state	get_delim(char *token);
char	**ft_realloc(char **str, size_t new_size);
char **set_envs(char **envs);
void	free_envs(char **my_envs);
static inline int is_delim(char *token)
{
    return (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
        || ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0);
}
static inline void    close_file_descriptors(t_params params)
{
    if (params.input_fd != STDIN_FILENO)
        close(params.input_fd);
    if (params.output_fd != STDOUT_FILENO)
        close(params.output_fd);
}
#endif