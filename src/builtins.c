/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/07/25 22:30:37 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_function(t_args *args, t_pid *proccess)
{
	kill(proccess->pid, SIGKILL);
	free_all(args, proccess);
	exit(1);
}