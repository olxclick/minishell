/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:47:37 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/17 11:47:38 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    verifica se a string e um inteiro valido e 
    verifica tambem se a string so tem digitos
*/
int	digits_in(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isdigit(arg[0]) && !(arg[0] == '-') && !(arg[0] == '+'))
		return (1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i += 1;
	}
	return (0);
}

/*
    da handle ao exit command e determina o seu
    exit status , da print a mensagem apropriada
    de acordo com o numero de argumentos
*/
long int	do_exit(t_args *expr, long int mini_exit, bool flag)
{
	if (flag)
		printf("exit\n");
	if (expr->len >= 3)
	{
		mini_exit = 1;
		if (flag)
			printf("exit: too many arguments\n");
	}
	else if (expr->len == 2)
	{
		if (digits_in((char *)expr->args[1])
			|| ft_atoi(expr->args[1]) > INT_MAX)
		{
			if (flag)
				printf("%s: numeric argument required\n",
					(char *)expr->args[1]);
			mini_exit = 2;
		}
		else
			mini_exit = ft_atoi(expr->args[1]);
	}
	return (mini_exit);
}

int	ver_exit(t_list *expressions, t_args *expr, t_params *params, bool flag)
{
	long int	mini_exit;

	mini_exit = 0;
	if (check_for_pipe(expressions) || params->exit_flag)
	{
		params->exit_flag = 1;
		if (expr->args[1])
			g_exit = ft_atoi(expr->args[1]);
		return (g_exit);
	}
	else
		mini_exit = do_exit(expr, mini_exit, flag);
	params->exit_flag = 0;
	params->exited = 1;
	return ((int)mini_exit);
}
