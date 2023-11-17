/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasferre <vasferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/11/06 15:57:57 by vasferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    printa o diretorio atual
*/
int	do_pwd(t_args *expr, bool flag)
{
	char	cwd[PATH_MAX];

	(void)expr;
	if (flag)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	return (0);
}

/*
    funcao responsavel por executar os builtins
    no child process, verifica o nome do comando
    na estrutura "expr" e chama a funcao para 
    tratar do built in
*/
int	exec_child_builtin(t_list *expressions, t_args *expr, t_envs *my_envs,
		bool flag)
{
	(void)expressions;
	if (ft_strcmp(expr->args[0], "echo") == 0)
		g_exit = do_echo(expr, flag);
	else if (ft_strcmp(expr->args[0], "pwd") == 0)
		g_exit = do_pwd(expr, flag);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs, flag);
	return (g_exit);
}

/*
    funcao responsavel por executar os parent builtins
    verifica o nome do comando
    na estrutura "expr" e chama a funcao para 
    tratar do built in
*/
int	exec_parent_builtin(t_list *expressions, t_params *params,
		t_envs *my_envs, bool flag)
{
	t_args	*expr;

	expr = expressions->content;
	if (ft_strcmp(expr->args[0], "exit") == 0)
		g_exit = ver_exit(expressions, expr, params, flag);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		g_exit = do_env(my_envs, flag);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs, flag);
	else if (ft_strcmp(expr->args[0], "unset") == 0)
		g_exit = do_unset(expr, my_envs, flag);
	else if (ft_strcmp(expr->args[0], "cd") == 0)
		g_exit = dir_change(expressions, expr, my_envs, flag);
	return (g_exit);
}

/*
    procura pelo delimitador e printa 
    uma mensagem de erro caso encontre
*/
int	check_delim(t_args *expr, bool flag)
{
	size_t	j;

	j = -1;
	while (++j < expr->len)
		if (ft_strcmp(expr->args[j], ">") == 0 || ft_strcmp(expr->args[j],
				"<") == 0 || ft_strcmp(expr->args[j], ">>") == 0
			|| ft_strcmp(expr->args[j], "<<") == 0 || ft_strcmp(expr->args[j],
				"|") == 0 || ft_strcmp(expr->args[j], "||") == 0)
		{
			if (flag)
				printf("Error: character is not allowed with echo\n");
			return (1);
		}
	return (0);
}

/*
    verifica a existncia de um pipe da return de 1
    casotenha sido encontrado e de 0 caso nao seja
    nao contrado
*/
int	check_for_pipe(t_list *expressions)
{
	int		i;
	t_args	*expr;

	i = 0;
	while (expressions->next)
	{
		expr = expressions->content;
		if (expr->state == PIPE)
			i++;
		expressions = expressions->next;
	}
	return (i);
}
