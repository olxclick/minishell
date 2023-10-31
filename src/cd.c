/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:14 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/31 16:15:31 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
 da update ao pwd dando free ao ultimo valor que tinha
 sido guardada antes e alloca o novo valor do pwd 
*/
void	update_pwd(t_envs *envs)
{
	int	pwd_pos;
	int	oldpwd_pos;

	pwd_pos = pos_env_var(envs, "PWD");
	oldpwd_pos = pos_env_var(envs, "OLDPWD");
	if (envs->oldpwd)
		free(envs->oldpwd);
	envs->oldpwd = getcwd(envs->buf, PATH_MAX);
	free(envs->vars[oldpwd_pos]);
	free(envs->vars[pwd_pos]);
	envs->vars[pwd_pos] = ft_strjoin("PWD=", envs->oldpwd);
	envs->vars[oldpwd_pos] = ft_strjoin("OLDPWD=", envs->pwd);
}

/*
	funcao responsavel por adquirir o valor de home
*/
char	*get_home(t_envs *my_envs, char *value)
{
	int	dir;
	int	start;

	dir = 0;
	dir = pos_env_var(my_envs, "HOME");
	start = get_lenght(my_envs, dir);
	value = ft_substr(my_envs->vars[dir], start, ft_strlen(my_envs->vars[dir]));
	return (value);
}

/*
	verifica o path que e dado, ve se existe
	se e valido e da handle a alguns erros
*/
char	*check_cd(t_args *expr, char *value, bool flag)
{
	struct stat	buf;

	if (stat(expr->args[1], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			if (flag)
				value = ft_strdup(expr->args[1]);
		}
		else
		{
			if (flag)
				printf("cd: path is not a directory\n");
			g_exit = 1;
		}
	}
	else
	{
		if (flag)
			printf("cd: unable to access path\n");
		g_exit = 1;
	}
	return (value);
}

void	get_oldpwd(t_envs *envs)
{
	free(envs->oldpwd);
	envs->oldpwd = ft_substr(envs->vars[pos_env_var(envs, "OLDPWD")],
								7,
								ft_strlen(envs->vars[pos_env_var(envs,
											"OLDPWD")]));
}

/*
	funcao responsavel por dar handle a operacoes
	do mudanca de diretorio consoante o argumento
	, caso um pipe seja dado comoargumento retorna null
*/
char	*change_dir(t_list *expressions, t_args *expr, t_envs *my_envs,
		char *value, bool flag)
{
	if (check_for_pipe(expressions))
		return (NULL);
	if ((expr->len == 1 || (!ft_strcmp(expr->args[1], "~") && expr->len == 2)))
	{
		g_exit = 0;
		if (flag)
			value = get_home(my_envs, value);
	}
	else if (ft_strcmp(expr->args[1], "-") == 0 && expr->len == 2 && flag)
	{
		g_exit = 0;
		if (flag)
		{
			if (my_envs->oldpwd)
				get_oldpwd(my_envs);
			value = ft_strdup(my_envs->oldpwd);
		}
	}
	else if (expr->args[1] && expr->len == 2)
		value = check_cd(expr, value, flag);
	return (value);
}

/*
	funcao responsavel por mudar o diretorio atual consoante o argumento
	dado
*/
int	dir_change(t_list *expressions, t_args *expr, t_envs *my_envs, bool flag)
{
	char	*value;

	value = NULL;
	my_envs->buf = NULL;
	if (expr->len > 2)
	{
		if (flag)
			printf("cd: invalid number of arguments\n");
		g_exit = 2;
	}
	else
		value = change_dir(expressions, expr, my_envs, value, flag);
	if (chdir(value) == 0 && flag)
		update_pwd(my_envs);
	cd_free(value, my_envs);
	return (g_exit);
}
