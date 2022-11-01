# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 18:20:52 by harndt            #+#    #+#              #
#    Updated: 2022/10/31 22:00:11 by harndt           ###   ########.fr        #
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

# ==============================================================================
# VARIABLES
# ==============================================================================

NAME	:=	minishell
CC		:=	cc
CFLAGS	:=	-g3 -Wall -Werror -Wextra
HEADERS	:=	includes
LIBFT	:=	./libft/libft.a
SRCS	:=	minishell.c  \
			$(PROMPT)/prompt.c \
			$(TOKENIZATION)/tokenizer.c $(TOKENIZATION)/quote_tokenizer.c \
			$(TOKENIZATION)/token_list.c $(TOKENIZATION)/token_utils.c \
			$(TOKENIZATION)/io_file_tokenizer.c  $(TOKENIZATION)/pipe_tokenizer.c \
			$(TOKENIZATION)/heredoc_tokenizer.c $(TOKENIZATION)/command_tokenizer.c\
			$(ERROR_HANDLERS)/error_handlers.c $(ERROR_HANDLERS)/error_handlers_utils.c \
			$(INIT_MS)/init_ms.c \
			$(FREE_MS)/free_ms.c \
			$(DEBUG)/debug.c \
			$(SIGNAL)/signal.c
OBJS	:=	$(SRCS:.c=.o)

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
			@valgrind -s --leak-check=full --show-leak-kinds=all 	\
			--gen-suppressions=yes --verbose --log-fd=9 			\
			./$(NAME) 9>memcheck.log

.PHONY:		all clean fclean re