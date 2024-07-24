# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/07/24 20:28:43 by itahri           ###   ########.fr        #
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

LIBFT = libft.a

NAME = ./minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo "compiling libft"
	@make -C ./libft
	@echo "libft compilation done"

$(NAME) : $(OBJS)
	@$(CC) $(C_FLAGS) -L ./libft -lft $^ -o $@
	@echo "executable ./minishell created"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(C_FLAGS) -c $< -o $@

clean : 
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libft
	@echo "🧼🧼objects cleaned🧼🧼"
	

fclean : clean
	rm -rf $(NAME)
	make fclean -C ./libft
	@echo "🧼🧼executable cleaned🧼🧼"

re : fclean all

.PHONY : all clean fclean re 
