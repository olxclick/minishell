/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:01:40 by jbranco-          #+#    #+#             */
/*   Updated: 2023/09/14 14:49:28 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Restora o termianl quando o usuario faz Ctrl + c;
rl_replace_line = troca a linha atual por uma string vazia
para agar qualquer texto escrito na linha atual

rl_on_new_line = sertifica que o programa vai para a linha seguinte

rl_redisplay = certifica que o terminal esta pronto para o input
feito pelo utilizador

*/

void	sigint_handler(int sig) //ctrl + c
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigquit_handler(int sig) // ctrl + backslash
{
	
	(void)sig;
}