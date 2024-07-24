# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/07/24 19:28:33 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = srcs/

PARSING = $(addprefix parsing/, parser.c queue_functions.c)

GARBAGE = $(addprefix garbage_collecting/, garbage_collector.c garbage_queue_funcs.c)

OBJS_DIR = .objets/

SRCS = $(PARSING) $(GARBAGE)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

NAME = ./minishell

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) $^ -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(DIR_DUP)
	$(CC) $(C_FLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 
