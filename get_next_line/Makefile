# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 18:37:54 by jbranco-          #+#    #+#              #
#    Updated: 2023/03/27 23:07:58 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAND = get_next_line.c get_next_line_utils.c

OBJ_MAND = $(MAND:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror -fPIE

NAME = get_next_line.a

all: $(NAME)

$(NAME): $(OBJ_MAND)
	ar rc $(NAME) $(OBJ_MAND)

clean:
	rm -rf $(OBJ_MAND)

fclean: clean
	rm -f $(NAME)

re : fclean all
