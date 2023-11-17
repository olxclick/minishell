# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:31:03 by jbranco-          #+#    #+#              #
#    Updated: 2023/11/17 11:59:45 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c src/lexer.c src/utils.c src/expander.c src/cd.c src/signals.c src/redirs.c src/builtins.c src/parser.c src/frees.c src/envs.c src/handler.c src/executor.c src/initializer.c src/redirs_utils.c src/tokenize.c src/path.c src/parser_utils.c src/export.c src/expander_utils.c src/exit.c src/echo.c src/executor_utils.c src/cd_utils.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fPIE -fsanitize=address -g3
LIBFT_A = libft/libft.a
GET_NEXT_LINE = ./get_next_line/get_next_line.a

all: $(NAME) clear

$(NAME): $(OBJS) $(LIBFT_A) $(GET_NEXT_LINE)
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT_A) $(GET_NEXT_LINE)

$(LIBFT_A):
	make bonus -C libft

$(GET_NEXT_LINE):
	make -C get_next_line

clear:
	clear

clean:
	rm -rf $(OBJS)
	make clean -C libft
	make clean -C get_next_line

fclean: clean
	rm -rf $(NAME) $(LIBFT_A) $(GET_NEXT_LINE)

re: fclean all
