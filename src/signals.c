/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasferre <vasferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:01:40 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/18 15:53:00 by vasferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"  

void signals(int sig)
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

/*
Restora o termianl quando o usuario faz Ctrl + c;
rl_replace_line = troca a linha atual por uma string vazia
para agar qualquer texto escrito na linha atual

rl_on_new_line = sertifica que o programa vai para a linha seguinte

rl_redisplay = certifica que o terminal esta pronto para o input
feito pelo utilizador

*/
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

void	back_slash(int sig)
{
	g_exit = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}