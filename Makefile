# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/08/28 12:48:56 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c src/tokening.c src/builtins.c src/parser.c src/frees.c src/envs.c src/handler.c src/executor.c
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
	make clean -C libft

fclean: clean
	rm -rf $(NAME) $(LIBFT_A)

re: fclean all
