# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/06/28 14:10:08 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c src/utils.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fPIE

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) 

re: clean all
