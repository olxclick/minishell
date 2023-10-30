/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:02:15 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/30 14:49:12 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    printa o diretorio atual
*/
int	do_pwd(t_args *expr)
{
	(void)expr;
	char	cwd[PATH_MAX];
	printf("%s\n", getcwd(cwd, PATH_MAX));
	return (0);
}

/*
    funcao responsavel por executar os builtins
    no child process, verifica o nome do comando
    na estrutura "expr" e chama a funcao para 
    tratar do built in
*/
int	exec_child_builtin(t_list *expressions, t_args *expr, t_envs *my_envs)
{
	(void)expressions;
	if (ft_strcmp(expr->args[0], "echo") == 0)
		g_exit = do_echo(expr);
	else if (ft_strcmp(expr->args[0], "pwd") == 0)
		g_exit = do_pwd(expr);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs);
	return (g_exit);
}

/*
    funcao responsavel por executar os parent builtins
    verifica o nome do comando
    na estrutura "expr" e chama a funcao para 
    tratar do built in
*/
int	exec_parent_builtin(t_list *expressions, t_args *expr, t_params *params, t_envs *my_envs)
{
	if (ft_strcmp(expr->args[0], "exit") == 0)
		g_exit = ver_exit(expressions, expr, params);
	else if (ft_strcmp(expr->args[0], "env") == 0)
		g_exit = do_env(my_envs);
	else if (ft_strcmp(expr->args[0], "export") == 0)
		g_exit = do_export(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "unset") == 0)
		g_exit = do_unset(expr, my_envs);
	else if (ft_strcmp(expr->args[0], "cd") == 0)
		g_exit = dir_change(expressions, expr, my_envs);
	return (g_exit);
}

/*
    remove variaves numa posicao exata na estrutura
    "my_envs", da tambem update na lista
*/
int	remove_var(t_envs *my_envs, int pos)
{
	if (pos == my_envs->len - 1)
		free(my_envs->vars[pos]);
	else
	{
		free(my_envs->vars[pos]);
		while (pos != my_envs->len - 1)
		{
			my_envs->vars[pos] = my_envs->vars[pos + 1];
			pos++;
		}
	}
	my_envs->vars[pos] = NULL;
	my_envs->len--;
	return (0);
}

/*
    percorre pelas variaveis , encontra a posicao
    e remove-as. caso o nome nao seja especificado ou
    nao seja encontrado da return de 0
*/
int	do_unset(t_args *expr, t_envs *my_envs)
{
	int	i;
	int	pos;

	i = 1;
	if (expr->len > 1)
	{
		while (i < my_envs->len && expr->args[i])
		{
			pos = pos_env_var(my_envs, expr->args[i]);
			if (pos < 0)
			{
				printf("'%s' could not be found\n", expr->args[i]);
				g_exit = 1;
			}
			else
				g_exit = remove_var(my_envs, pos);
			i++;
		}
	}
	else
	{
		printf("unset: invalid Syntax\n");
		g_exit = 1;
	}
	return (g_exit);
}

/*
    adiciona ou da update as variaveis
    pega o nome da variavel atraves da "envs"
    encontra a sua posicao e adiciona ou da update
    na variavel
*/
int	add_env(t_envs *envs, char *expr)
{
	size_t	i;
	int		pos;
	char	*key;

	i = 0;
	while (expr[i] && expr[i] != '=')
		i++;
	key = ft_substr(expr, 0, i);
	pos = pos_env_var(envs, key);
	if (pos == -1)
	{
		envs->len++;
		envs->vars = ft_realloc(envs->vars, envs->len);
		envs->vars[envs->len - 1] = ft_strdup(expr);
	}
	else
	{
		free(envs->vars[pos]);
		envs->vars[pos] = ft_strdup(expr);
	}
	// envs->vars[envs->len] = NULL;
	free(key);
	return (0);
}

int	do_export(t_args *expr, t_envs *envs)
{
	int	i;

	if (expr->len == 1)
	{
		sort_envs(envs);
		return (0);
	}
	i = 1;
	while (expr->args[i])
	{
		if (expr->args[i] && isalnum(expr->args[i][0]))
			g_exit = add_env(envs, expr->args[i]);
		i++;
	}
	if (g_exit > 0)
		g_exit = 1;
	return (g_exit);
}

/*
    procura pelo delimitador e printa 
    uma mensagem de erro caso encontre
*/
int	check_delim(t_args *expr)
{
	size_t	j;

	j = -1;
	while (++j < expr->len)
		if (ft_strcmp(expr->args[j], ">") == 0
			|| ft_strcmp(expr->args[j], "<") == 0
			|| ft_strcmp(expr->args[j], ">>") == 0
			|| ft_strcmp(expr->args[j], "<<") == 0
			|| ft_strcmp(expr->args[j], "|") == 0
			|| ft_strcmp(expr->args[j], "||") == 0)
			return (printf("Error: character is not allowed with echo\n"));
	return (0);
}

/*
    replica as funcionalidades do echo e 
    ignora o "\" e o "-n"
*/
int	do_echo(t_args *expr)
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = 1;
	if (expr->len == 1)
		printf("\n");
	if (expr->args[1])
	{
		if (ft_strcmp(expr->args[1], "\\") == 0)
			return (0);
		if (ft_strncmp(expr->args[1], "-n", 2) == 0)
			i = 2;
		else
			i = 1;
	}
	if (check_delim(expr))
		return (1);
	while (expr->args[i])
	{
		if (flag)
			printf(" ");
		printf("%s", expr->args[i++]);
		if (expr->args[i])
			flag = 1;
		else
			flag = 0;
	}
	if (expr->args[1])
		if (ft_strncmp(expr->args[1], "-n", 2) != 0)
			printf("\n");
	return (0);
}

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
    verifica a existncia de um pipe da return de 1
    casotenha sido encontrado e de 0 caso nao seja
    nao contrado
*/
int	check_for_pipe(t_list *expressions)
{
	int	i;

	i = 0;
   	while (expressions->next)
   	{
		t_args *expr = expressions->content;
		if (expr->state == PIPE)
			i++;
		expressions = expressions->next;
    	}
	return (i);
}

/*
    da handle ao exit command e determina o seu
    exit status , da print a mensagem apropriada
    de acordo com o numero de argumentos
*/
long int	do_exit(t_args *expr, long int mini_exit)
{
	printf("exit\n");
	if (expr->len >= 3)
	{
		mini_exit = 1;
		printf("exit: too many arguments\n");
	}
	else if (expr->len == 2)
	{
		if (digits_in((char *)expr->args[1]) || ft_atoi(expr->args[1]) > INT_MAX)
		{
			printf("%s: numeric argument required\n",
				(char *)expr->args[1]);
			mini_exit = 2;
		}
		else
			mini_exit = ft_atoi(expr->args[1]);
	}
	return (mini_exit);
}

int	ver_exit(t_list *expressions, t_args *expr, t_params *params)
{
	long int mini_exit;

	mini_exit = 0;
	if (check_for_pipe(expressions) || params->exit_flag)
	{
		params->exit_flag = 1;
		if (expr->args[1])
			g_exit = ft_atoi(expr->args[1]);
		return (g_exit);
	}
	else
		mini_exit = do_exit(expr, mini_exit);
	params->exit_flag = 0;
	params->exited = 1;
	return ((int)mini_exit);
}
