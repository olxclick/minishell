/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:01:40 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/27 14:13:05 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, restore);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
}

void	restore(int sig)
{
	g_exit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_exit = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig) //ctrl + backslash
{
	g_exit = 131;
	printf("Quit (core dumped)\n");
	signal(SIGQUIT, SIG_IGN);
	(void)sig;
}
