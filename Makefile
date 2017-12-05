# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tperraut <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 15:54:33 by tperraut          #+#    #+#              #
#*   Updated: 2016/05/19 23:38:02 by tperraut         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

##########
# TARGET #
##########

NAME = fillit

############
# COMPILER #
############

CC = clang
CFLAGS = -Werror -Wall -Wextra

#######
# LIB #
#######

LIB = -lft
LIB_DIR = ./libft
LIB_INC = -I $(LIB_DIR)/include

##########
# HEADER #
##########

INC = -I ./include

##########
# SOURCE #
##########

SRC_DIR = ./src/
SRC_NAME = \
	ft_accept.c \
	ft_resolve.c \
	ft_affiche.c \
	ft_add_trio.c \
	ft_remove_trio.c \
	ft_free_mat.c \
	ft_create_mat.c \
	ft_putpt.c \
	ft_pset.c \
	parser.c \
	main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))

##########
# OBJECT #
##########

OBJ_DIR = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

#########
# RULES #
#########

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_INC) $(INC) -L $(LIB_DIR) $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(LIB_INC) $(INC)

clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
