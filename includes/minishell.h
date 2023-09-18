/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/18 14:29:53 by jbranco-         ###   ########.fr       */
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
# include <linux/limits.h>
# include <fcntl.h>
# include <stdint.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

#define W 1
#define R 0
#define DOUBLE_QUOTE '"'
#define SINGLE_QUOTE '\''

extern int	g_exit;

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

typedef struct s_envs
{
	char	**vars;
	int	len;
}			t_envs;

typedef struct s_params
{
	int	pipe_fd[2];
	int	*files;
	int	input_fd;
	int	output_fd;
	long long	exit_status;
	pid_t	pid;
	size_t	exited;
}			t_params;

typedef struct s_token
{
	char	**token;
}			t_token;

void	loop(t_envs *my_envs);
char	*get_path(char *expr, t_envs *envs);
int	is_builtin(char *cmd);
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
size_t	process(char *input, t_envs *my_envs);
t_envs	*init_envs(t_envs *my_envs, char **envs);
void	do_exit(t_args *expr, t_params *params);
void	do_echo(t_args *expr);
int	search_var(t_envs *envs, char *to_find);
t_token set_args_tokens(char *input);
size_t	count_quotes(char *str);
void	exec(t_args *expr, t_envs *my_envs);
t_params	init_params(t_list *expresisons);
char	*redo_token(char *input, char c);
void   executor(t_list *expressions, t_envs *envs, t_params *params);
t_args    *get_parsed(t_token t);
int	*create_files(t_list *expressions);
void	free_list(t_list* list);
void	do_env(t_envs *my_envs);
char	*get_token(char *input);
char	*remove_quotes(char *input);
void	copy_free(t_envs *my_envs);
int	pos_env_var(t_envs *envs, char *find);
char	*check_token(char *input);
char	**ft_realloc(char **str, size_t new_size);
void	sort_envs(t_envs *envs);
void	envs_printer(t_envs *envs);
void	do_redir_out(t_params *params);
int	get_envs_size(char **envs);
void	swap(char** a, char** b);
int	count_files_needed(t_list *expressions);
void	free_token(char **my_envs);
char	*operator_return(char *input, int i);
t_list    *get_all_tokens(t_token t);
char **get_args(t_token t, int end);
void	handle_pipes(t_list *expressions, t_params *parameters);
t_state	get_state(t_args *args, t_state prev_state);
void	do_export(t_args *expr, t_envs *envs);
void print_list(t_list *head);
void	do_unset(t_args *expr, t_envs *my_envs);
t_state	get_delim_state(char *token);
void	exec_parent_builtin(t_args *expr, t_params *params, t_envs *my_envs);
char **set_envs(char **envs);
void	exec_child_builtin(t_args *expr, t_params *params);
void	free_envs(t_envs *my_envs);
void	ignore_signals();
static inline int is_delim(char *token)
{
    return (ft_strcmp(token, "|") == 0) || (ft_strcmp(token, "<") == 0) || (ft_strcmp(token, ">") == 0)
        || (ft_strcmp(token, "<<") == 0) || (ft_strcmp(token, ">>") == 0);
}
static inline void    close_file_descriptors(t_params *params)
{
    if (params->input_fd != STDIN_FILENO)
        close(params->input_fd);
    if (params->output_fd != STDOUT_FILENO)
        close(params->output_fd);
}
#endif