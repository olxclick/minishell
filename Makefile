# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/07/26 17:23:17 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = minishell.c src/utils.c src/builtins.c src/parser.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fPIE
LIBFT_A = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT_A) && ./minishell

$(LIBFT_A):
	make bonus -C libft

clean:
	rm -rf $(OBJS)

fclean: clean
	make clean -C libft
	rm -rf $(NAME) $(LIBFT_A)

re: fclean all
