# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/08/04 16:58:23 by madamou          ###   ########.fr        #
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

ERROR = $(addprefix errors/, error_file.c handle_functions.c)

EXEC = $(addprefix execution/, check_cmd.c exec_commands.c exec_utils.c operator.c redirections.c exit_code.c)

SIGNALS = $(addprefix signal/, signal.c)

BINARY_TREE = $(addprefix binary_tree/, lexing.c lexer_utils.c)

PROMPT = $(addprefix receive_prompt/, receive_prompt.c)

BUILTINS = $(addprefix builtins/, env.c cd.c echo.c export.c pwd.c exit.c)

ENV = $(addprefix environement/, environement_varables.c)

UTILS = $(addprefix utils/, utils.c)

OBJS_DIR = .objets/

SRCS = main.c $(PARSING) $(GARBAGE) $(PROMPT) $(SIGNALS) $(BINARY_TREE) $(ERROR) $(EXEC) $(ENV) $(UTILS) $(BUILTINS)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

G				= $(BLUE)
X 				= \e[0m
BAR_SIZE		= 50

TOTAL_FILES		:= $(words $(SRCS))
COMPILED_FILES	:= 0

LIBFT = libft.a

NAME = ./minishell

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo
	@echo "👷$(GREEN)compiling libft$(END)👷"
	@make -sC ./libft
	@echo
	@echo "👷$(GREEN)libft compilation done$(END)👷"

$(NAME) : message $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) -L ./libft -lft -lreadline -o $@
	@echo
	@echo "💻$(BLUE)executable created >_$(END)✅"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(C_FLAGS) -c $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n ""
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " ($(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%) "
	@echo -n ""
	@printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
	@echo -n " "
	@printf "%s" $(notdir $<)
	@printf "\e[0K\r"

message :
	@echo
	@echo "$(BLUE)🔩compiling minishell🔩$(END)"
	
leak : all
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=.supp.supp ./minishell

push: fclean
	@python3 -m c_formatter_42 */*.c */*.h */*/*.c */*/*.h | norminette | grep Error
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

debug : all
	@lldb $(NAME)

docker:
	@if [ -z $$(docker images -q minishell-app) ]; then \
		echo "🐳$(BLUE)Image minishell-app not found, work in progress...$(END)🐳"; \
		docker-compose build; \
		echo "🐳$(BLUE)Docker container is built $(END)✅"; \
	fi
	@echo "🐳$(BLUE)Docker container is built $(END)✅"
	@docker-compose run app

clean : 
	@rm -rf $(OBJS_DIR)
	@make clean -sC ./libft
	@echo "🧼🧼$(PURPLE)objects cleaned$(END)🧼🧼"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -sC ./libft
	@echo "🧼🧼$(PURPLE)executable cleaned$(END)🧼🧼"

re : fclean all

.PHONY : all clean fclean re debug push leak docker 
