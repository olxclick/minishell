/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:01:40 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/12 00:29:07 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int exit_number;

void signals(int signal)
{
    if (signal == 1)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, restore);
    }
    if (signal == 2)
    {
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, back_slash);
    }
    if (signal == 3)
    {
        printf("exit\n");
        exit(0);
    }
}

/*
Restora o termianl quando o usuario faz Ctrl + c;
rl_replace_line = troca a linha atual por uma string vazia
para agar qualquer texto escrito na linha atual

rl_on_new_line = sertifica que o programa vai para a linha seguinte

rl_redisplay = certifica que o terminal esta pronto para o input
feito pelo utilizador

*/
void	restore(int signal)
{
	exit_number = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	ctrl_c(int signal)
{
	exit_number = 130;
	write(1, "\n", 1);
	(void)signal;
}

void	back_slash(int signal)
{
	exit_number = 131;
	printf("Quit (core dumped)\n");
	(void)signal;
}