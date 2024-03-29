/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:32:41 by jbranco-          #+#    #+#             */
/*   Updated: 2023/10/31 16:15:22 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	duplica um array de variaveis e guarda a copia
	para ser usado mais tarde
*/
char	**set_envs(char **envs)
{
	char	**my_envs;
	int		i;

	i = 0;
	my_envs = malloc((get_envs_size(envs) + 1) * sizeof(char *));
	while (envs[i])
	{
		my_envs[i] = ft_strdup(envs[i]);
		i++;
	}
	my_envs[i] = NULL;
	return (my_envs);
}

/*
	utiliza um loop para correr pelas variaveis
	guardas na struct "my_envs" e da print nelas
	retorna 0 caso tenho sido feito com sucesso
*/
int	do_env(t_envs *my_envs, bool flag)
{
	int	i;

	i = 0;
	while (i < my_envs->len && flag)
		printf("%s\n", my_envs->vars[i++]);
	return (0);
}

/*
	cria uma copia das variaveis e manda da source struct
	para a target strutc
*/
t_envs	*copy_envs(t_envs *new_envs, t_envs *envs)
{
	int	i;

	i = 0;
	new_envs->len = envs->len;
	new_envs->vars = malloc(envs->len * sizeof(char *));
	new_envs->oldpwd = NULL;
	new_envs->pwd = NULL;
	while (i < envs->len)
	{
		new_envs->vars[i] = ft_strdup(envs->vars[i]);
		i++;
	}
	return (new_envs);
}

void	sort_envs(t_envs *envs)
{
	t_envs	*envs_copy;
	int		i;
	int		j;

	i = 0;
	envs_copy = malloc(sizeof(t_envs));
	envs_copy = copy_envs(envs_copy, envs);
	while (i < envs->len)
	{
		j = 0;
		while (j < envs->len - i - 1)
		{
			if (strcmp(envs_copy->vars[j], envs_copy->vars[j + 1]) > 0)
				swap(&envs_copy->vars[j], &envs_copy->vars[j + 1]);
			j++;
		}
		i++;
	}
	envs_printer(envs_copy);
	copy_free(envs_copy);
}

/*
	da sort nas variaveis atraves de um bubble sorte
	da print nas mesmas e da free nas copias da variaveis
*/
void	envs_printer(t_envs *envs)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (i < envs->len)
	{
		j = 0;
		printf("declare -x ");
		while (envs->vars[i][j])
		{
			if (envs->vars[i][j] == '=')
				flag = 1;
			printf("%c", envs->vars[i][j]);
			if (flag)
				printf("\"");
			flag = 0;
			j++;
		}
		if (!envs->vars[i][j])
			printf("\"");
		printf("\n");
		i++;
	}
}
