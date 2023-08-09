# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 17:24:19 by mberrouk          #+#    #+#              #
#    Updated: 2023/08/08 01:23:21 by mberrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g3

IDFLAG		=	-I/Users/hoakoumi/homebrew/opt/readline/include

LDFLAG		=	-L/Users/hoakoumi/homebrew/opt/readline/lib -lreadline

SRCS =  utils/ft_split.c utils/linked_list_utils.c utils/utils_double_ptr.c utils/utils_err.c \
		utils/utils_strings.c utils/utils_strings1.c parsing/lexer.c parsing/parser.c parsing/parsing_utils.c\
		main.c exec.c  parsing/expansion_analysis.c parsing/expansion_in_doublq.c parsing/expansion_utils.c \
		parsing/expansion_utils2.c parsing/itoa.c env_process.c ft_printf.c clean_utils.c \
		Builtins/builtins.c Builtins/pwd.c Builtins/env.c Builtins/echo.c Builtins/exit.c  exec_utils.c\
		Builtins/outils_built.c Builtins/unset.c Builtins/cd.c Builtins/outils_buit1.c Builtins/outils_buils2.c Builtins/export.c herdoc.c

OBJ = ${SRCS:%.c=%.o}

CC = cc -g #-fsanitize=address -g3 #-Wall -Wextra -Werror  #-lncurses  -L -lreadline -L /Users/mberrouk/homebrew/opt/readline/include/readline -I ~/homebrew/opt/readline/include

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
