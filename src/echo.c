#include "includes/minishell.h"

/*
    replica as funcionalidades do echo e 
    ignora o "\" e o "-n"
*/

void	run_echo(t_args *expr, size_t i, size_t flag2)
{
	while (expr->args[i])
	{
		if (flag2 && i != 1)
			printf(" ");
		printf("%s", expr->args[i++]);
		if (expr->args[i])
			flag2 = 1;
		else
			flag2 = 0;
	}
}

int	do_echo(t_args *expr, bool flag)
{
	size_t	i;
	size_t	flag2;

	flag2 = 0;
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
	if (check_delim(expr, flag))
		return (1);
	run_echo(expr, i, flag2);
	if (expr->args[1])
		if (ft_strncmp(expr->args[1], "-n", 2) != 0)
			printf("\n");
	return (0);
}
