# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 17:24:19 by mberrouk          #+#    #+#              #
#    Updated: 2023/08/09 02:01:50 by hoakoumi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3

IDFLAG		=	-I/Users/hoakoumi/homebrew/opt/readline/include

LDFLAG		=	-L/Users/hoakoumi/homebrew/opt/readline/lib -lreadline

SRCS =  utils/ft_split.c utils/linked_list_utils.c utils/utils_double_ptr.c utils/utils_err.c \
		utils/utils_strings.c utils/utils_strings1.c parsing/lexer.c parsing/parser.c parsing/parsing_utils.c\
		main.c execution/exec.c  parsing/expansion_analysis.c parsing/expansion_in_doublq.c parsing/expansion_utils.c \
		parsing/expansion_utils2.c parsing/itoa.c parsing/env_process.c utils/ft_printf.c parsing/clean_utils.c execution/execution.c\
		Builtins/builtins.c Builtins/pwd.c Builtins/env.c Builtins/echo.c Builtins/exit.c  execution/exec_utils.c Builtins/export_utils3.c  \
		Builtins/outils_built.c Builtins/unset.c Builtins/cd.c Builtins/outils_buit1.c Builtins/outils_buils2.c Builtins/export.c execution/herdoc.c\
		execution/exec1.c  Builtins/export_utils.c Builtins/export_utils1.c  Builtins/export_utils2.c ultra_split.c parsing/parser_utils.c 

OBJ = ${SRCS:%.c=%.o}

CC = cc -g #-lncurses #-fsanitize=address -g3 #-Wall -Wextra -Werror  #-lncurses  -L -lreadline -L /Users/mberrouk/homebrew/opt/readline/include/readline -I ~/homebrew/opt/readline/include

all : ${NAME}

${NAME} :
	$(CC) -o $(NAME) $(IDFLAG) $(LDFLAG) $(CFLAGS) $(SRCS) 
	make clean
	clear
	#./minishell

#%.o : %.c
#	$(CC) $(CFLAGS) -c

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all
