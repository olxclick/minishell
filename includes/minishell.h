/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/09 15:14:21 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define W 1
# define R 0
# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''

extern int			g_exit;

typedef enum
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	DOC,
	DEFAULT
}					t_state;

typedef struct s_args
{
	char			**args;
	t_state			state;
	size_t			len;
}					t_args;

typedef struct s_envs
{
	char			**vars;
	char			*oldpwd;
	char			*buf;
	int				len;
}					t_envs;

typedef struct s_params
{
	int				pipe_fd[2];
	int				*files;
	int				input_fd;
	int				output_fd;
	int				heredoc_fd;
	long long		exit_status;
	pid_t			pid;
	size_t			exited;
}					t_params;

typedef struct s_token
{
	char			**token;
}					t_token;

void				loop(t_envs *my_envs);
char				*get_path(char *expr, t_envs *envs);
size_t				process(char *input, t_envs *my_envs);
t_envs				*init_envs(t_envs *my_envs, char **envs);
void				redirect(t_params *params);
int					get_lenght(t_envs *envs, int i);
int					do_heredoc(t_list *expressions, t_params *params);
int					do_exit(t_args *expr, t_params *params);
int					do_echo(t_args *expr);
int					search_var(t_envs *envs, char *find);
int					heredoc_checker(char *line, char *delim);
t_token				set_args_tokens(char *input, t_envs *envs);
size_t				count_quotes(char *str);
char				*check_cd(t_args *expr, char *value);
int					check_delim(t_args *expr);
int					get_envs_size(char **envs);
char				*get_var(char *input, t_envs *envs);
void				exec(t_args *expr, t_envs *my_envs, char *path, t_params *params);
void				swap(char **a, char **b);
t_params			init_params(t_list *expresisons);
int					pos_env_var(t_envs *envs, char *find);
char				*redo_token(char *input, char c, int flag, t_envs *envs);
void				executor(t_list *expressions, t_envs *envs,
						t_params *params);
t_args				*get_parsed(t_token t);
int					*create_files(t_list *expressions);
void				free_list(t_list *list);
int					do_env(t_envs *my_envs);
void				redir_input(t_list *expressions, t_params *params);
char				*get_token(char *input);
char				*remove_quotes(char *input);
void				copy_free(t_envs *my_envs);
int					pos_env_var(t_envs *envs, char *find);
char				*check_token(char *input, t_envs *envs);
char				**ft_realloc(char **str, size_t new_size);
void				sort_envs(t_envs *envs);
void				envs_printer(t_envs *envs);
int					dir_change(t_args *expr, t_envs *my_envs);
void				do_redir_out(t_params *params);
int					get_envs_size(char **envs);
int					is_same_quotes(char *str);
void				swap(char **a, char **b);
int					count_files_needed(t_list *expressions);
void				free_token(char **my_envs);
char				*get_home(t_envs *my_envs, char *value);
char				*operator_return(char *input, int i);
t_list				*get_all_tokens(t_token t);
void				signals(int sig);
void				cd_free(char *value, char *buffer, t_envs *my_envs);
void				restore(int sig);
void				ctrl_c(int sig);
void				update_pwd(t_envs *envs, char *buffer);
void				back_slash(int sig);
char				**get_args(t_token t, int end);
void				handle_pipes(t_list *expressions, t_params *parameters);
t_state				get_state(t_args *args, t_state prev_state);
int					read_fd(char *file_name);
int					child_process(t_list *expressions, t_envs *envs,
						t_params *params);
int					redir_needed(t_list *expressions);
int					do_export(t_args *expr, t_envs *envs);
void				print_list(t_list *head);
int					do_unset(t_args *expr, t_envs *my_envs);

t_state				get_delim_state(char *token);
int					exec_parent_builtin(t_args *expr, t_params *params,
						t_envs *my_envs);
char				**set_envs(char **envs);
int					exec_child_builtin(t_args *expr, t_params *params, t_envs *my_envs);

static inline int	is_delim(char *token)
{
	return ((ft_strcmp(token, "|") == 0) || (ft_strcmp(token, "<") == 0)
		|| (ft_strcmp(token, ">") == 0) || (ft_strcmp(token, "<<") == 0)
		|| (ft_strcmp(token, ">>") == 0));
}

static inline void	close_file_descriptors(t_params *params)
{
	if (params->input_fd != STDIN_FILENO)
		close(params->input_fd);
	if (params->output_fd != STDOUT_FILENO)
		close(params->output_fd);
}

static inline int	is_child_builtin(char *cmd)
{
	return ((ft_strcmp(cmd, "pwd") == 0) || (ft_strcmp(cmd, "echo") == 0));
}

static inline int	is_parent_builtin(char *cmd, int len)
{
	return ((ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "env") == 0 && len > 1)
		|| (ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "export") == 0 && len > 1)
		|| (ft_strcmp(cmd, "unset") == 0));
}
#endif