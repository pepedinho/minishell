# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/07/27 19:54:06 by itahri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
PURPLE			=	\033[0;35m
END= 	$(shell tput -Txterm sgr0)

CC = cc

C_FLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = srcs/

PARSING = $(addprefix parsing/, parser.c queue_functions.c)

GARBAGE = $(addprefix garbage_collecting/, garbage_collector.c garbage_queue_funcs.c)

SIGNALS = $(addprefix signal/, signal.c)

BINARY_TREE = $(addprefix binary_tree/, lexing.c)

PROMPT = $(addprefix receive_prompt/, receive_prompt.c)

OBJS_DIR = .objets/

SRCS = main.c $(PARSING) $(GARBAGE) $(PROMPT) $(SIGNALS) $(BINARY_TREE)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

LIBFT = libft.a

NAME = ./minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo "👷$(YELLOW)compiling libft$(END)👷"
	@make -C ./libft
	@echo "👷$(YELLOW)libft compilation done$(END)👷"

$(NAME) : $(OBJS)
	@$(CC) $(C_FLAGS) $^ -L ./libft -lft -lreadline -o $@
	@echo "💻$(BLUE)executable created ./minishell >_$(END)✅"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(C_FLAGS) -c $< -o $@

leak : all
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=.supp.supp ./minishell

push : fclean
	@python3 -m c_formatter_42 */*.c */*.h */*/*.c */*/*.c | sleep 1
	@norminette | grep Error
	@git add .
	@git commit -m $ARG
	git push
	@echo -n "$(YELLOW) All has been push with"
	@echo -n "'$(ARG)' in commit $(END)"

debug : all
	@lldb ./minishell

clean : 
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libft
	@echo "🧼🧼$(PURPLE)objects cleaned$(END)🧼🧼"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./libft
	@echo "🧼🧼$(PURPLE)executable cleaned$(END)🧼🧼"

re : fclean all

.PHONY : all clean fclean re debug
