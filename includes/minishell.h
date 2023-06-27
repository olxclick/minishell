/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:29:48 by jbranco-          #+#    #+#             */
/*   Updated: 2023/06/27 14:38:33 by jbranco-         ###   ########.fr       */
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
#define MAX_PATH_LENGTH 256

typedef struct s_args
{
	char	*expression[MAX_ARGS];
	size_t	len;
}			t_args;

int	process(char *input);
void	loop();
t_args	*format_input(char *input);
t_args	*initialize_args();

#endif