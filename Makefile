# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/09/28 13:19:27 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c src/lexer.c src/utils.c src/expander.c src/cd.c src/signals.c src/redirs.c src/builtins.c src/parser.c src/frees.c src/envs.c src/handler.c src/executor.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fPIE -fsanitize=address
LIBFT_A = libft/libft.a
GET_NEXT_LINE = ./get_next_line/get_next_line.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(GET_NEXT_LINE)
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT_A) $(GET_NEXT_LINE)

$(LIBFT_A):
	make bonus -C libft

$(GET_NEXT_LINE):
	make -C get_next_line

clean:
	rm -rf $(OBJS)
	make clean -C libft
	make clean -C get_next_line

fclean: clean
	rm -rf $(NAME) $(LIBFT_A) $(GET_NEXT_LINE)

re: fclean all
