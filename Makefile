# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/07/26 00:01:56 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c src/utils.c src/builtins.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fPIE

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) && ./minishell

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) 

re: clean all
