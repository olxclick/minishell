#include "includes/minishell.h"

char	*get_token(char *input)
{
	i = 0;
	c = '\0';
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
		{
			if (!c)
				c = input[i];
			else if (input[i] == c)
				c = '\0';
		}
		if (i == 0 && (input[i] == '|' || input[i] == '>' || input[i] == '<'))
			return (operator_return(input, i));
		else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>'
				|| input[i] == '<') && !c)
			return (ft_substr(input, 0, i));
		else if (input[i + 1] == '\0')
			return (ft_substr(input, 0, i + 1));
		i++;
	}
	return (NULL);
}

char	*operator_return(char *input, int i)
{
	char	*token;

	token = NULL;
	if (input[i] == '|' && input[i + 1] == '|')
		token = ft_substr(input, 0, sizeof("||") - 1);
	else if (input[i] == '|')
		token = ft_substr(input, 0, sizeof("|") - 1);
	else if (input[i] == '>' && input[i + 1] == '>')
		token = ft_substr(input, 0, sizeof(">>") - 1);
	else if (input[i] == '<' && input[i + 1] == '<')
		token = ft_substr(input, 0, sizeof("<<") - 1);
	else if (input[i] == '>')
		token = ft_substr(input, 0, sizeof(">") - 1);
	else if (input[i] == '<')
		token = ft_substr(input, 0, sizeof("<") - 1);
	return (token);
}

int	quote_return(char *str)
{
	if (str[0] == SINGLE_QUOTE)
		return (2);
	else if (str[0] == DOUBLE_QUOTE)
		return (1);
	return (0);
}
