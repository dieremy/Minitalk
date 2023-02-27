# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 11:57:20 by robegarc          #+#    #+#              #
#    Updated: 2023/02/27 12:05:54 by robegarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
OBJ = $(SRC:.c=.o)
CC = gcc -Wall -Wextra -Werror
NAME = minitalk
LIBFT = libft
FT_PRINTF = ft_printf
LIBRARY = ft_printf/libftprintf.a libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(FT_PRINTF)
	make -C $(LIBFT)
	$(CC) $(OBJ) $(LIBRARY) -o $(NAME)
clean :
	make clean -C $(FT_PRINTF)
	make clean -C $(LIBFT)
	rm -f $(OBJ)
fclean : clean
	make fclean -C $(FT_PRINTF)
	make fclean -C $(LIBFT)
	rm -f $(NAME)
re : fclean clean all

.PHONY: clean fclean re all
