# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 18:20:52 by harndt            #+#    #+#              #
#    Updated: 2023/01/16 21:56:14 by bbonaldi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# PATH
# ==============================================================================

TOKENIZATION	:= tokenization
INIT_MS 		:= init_ms
FREE_MS 		:= free_ms
PROMPT			:= prompt
SIGNAL			:= signal
ERROR_HANDLERS	:= error_handlers
DEBUG			:= debug
ENV				:= env
PARSER			:= parser
EXECUTOR		:= executor
BUILTIN			:= builtin

# ==============================================================================
# VARIABLES
# ==============================================================================

NAME	:=	minishell
CC		:=	cc
CFLAGS	:=	-g3 -Wall -Werror -Wextra
HEADERS	:=	includes
LIBFT	:=	./libft/libft.a
SRCS	:=	minishell.c \
			$(PROMPT)/prompt.c \
			$(TOKENIZATION)/tokenizer.c $(TOKENIZATION)/quote_tokenizer.c \
			$(TOKENIZATION)/token_list.c $(TOKENIZATION)/token_utils.c \
			$(TOKENIZATION)/io_file_tokenizer.c  $(TOKENIZATION)/pipe_tokenizer.c \
			$(TOKENIZATION)/heredoc_tokenizer.c $(TOKENIZATION)/command_tokenizer.c \
			$(TOKENIZATION)/expansion_handler.c \
			$(ERROR_HANDLERS)/error_handlers.c $(ERROR_HANDLERS)/error_handlers_utils.c \
			$(ERROR_HANDLERS)/error_handlers_2.c \
			$(INIT_MS)/init_ms.c \
			$(FREE_MS)/free_ms.c \
			$(DEBUG)/debug.c $(DEBUG)/debug_utils.c \
			$(ENV)/hash_table.c $(ENV)/hash_table_utils.c \
			$(ENV)/hash_table_clear.c $(ENV)/hash_table_init.c \
			$(ENV)/hash_table_delete.c $(ENV)/hash_table_insert.c \
			$(ENV)/env.c $(ENV)/env_2.c \
			$(PARSER)/parser.c $(PARSER)/init_tree.c $(PARSER)/free_tree.c \
			$(PARSER)/parser_utils.c \
			$(EXECUTOR)/executor.c $(EXECUTOR)/commands_builder.c \
			$(EXECUTOR)/fd_handler_pipe.c $(EXECUTOR)/fd_handler_utils.c \
			$(EXECUTOR)/fd_handler_redirection.c $(EXECUTOR)/fd_handler_redirection_utils.c \
			$(EXECUTOR)/heredoc_handler.c $(EXECUTOR)/wait.c \
			$(BUILTIN)/ms_cd.c	$(BUILTIN)/ms_echo.c	$(BUILTIN)/ms_env.c \
			$(BUILTIN)/ms_exit.c	$(BUILTIN)/ms_export.c	$(BUILTIN)/ms_pwd.c \
			$(BUILTIN)/ms_unset.c	$(BUILTIN)/ms_utils.c	\
			$(SIGNAL)/signal.c
			
OBJS	:=	$(SRCS:.c=.o)
VGSUPRESS	:= --suppressions=readline.supp

# ==============================================================================
# COLORS
# ==============================================================================

GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
WHT			:=	\033[1;37m
EOC			:=	\033[1;0m

# ==============================================================================
# RECIPES
# ==============================================================================

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT)
			@echo "$(WHT)Compiling MINISHELL...$(EOC)"
			@$(CC) $(OBJS) $(LIBFT) -lreadline  -o $@
			@echo "$(GREEN)MINISHELL build completed.$(EOC)"

$(LIBFT):
			@make -C libft

clean:
			@echo "$(WHT)Removing .o files...$(EOC)"
			@rm -f $(OBJS)
			@make -C libft clean
			@echo "$(GREEN)Clean done.$(EOC)"

fclean:		clean
			@echo "$(WHT)Removing object- and binary -files...$(EOC)"
			@rm -f $(NAME)
			@make -C libft fclean
			@echo "$(GREEN)Fclean done.$(EOC)"

re:			fclean all

valgrind:
			@valgrind $(VGSUPRESS) -s --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --trace-children=yes --log-fd=9 ./$(NAME) 9>memcheck.log

valgrind_track:
			@valgrind $(VGSUPRESS) -s --leak-check=full --show-leak-kinds=all \
			   --trace-children=yes --track-fds=yes --log-fd=9 ./$(NAME) 9>memcheck.log

.PHONY:		all clean fclean re