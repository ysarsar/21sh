# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 00:51:07 by ommadhi           #+#    #+#              #
#    Updated: 2020/03/11 05:55:12 by ysarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  readline/ft_autocomp2.c\
		readline/ft_copy.c\
		readline/ft_multi_line.c\
		readline/ft_mv_cursor.c\
		readline/ft_press_key.c\
		readline/ft_readline.c\
		readline/ft_save_history.c\
		readline/get_cur_posix.c\
		readline/ft_scroll.c\
		readline/ft_add_and_del_char.c\
		readline/ft_goto.c\
		readline/ft_ctr_c.c\
		readline/ft_free_his.c\
		readline/ft_print_his.c\
		readline/ft_autoco_search.c\
		src/builtins.c\
	   	src/environement.c\
	   	src/execute_pipe.c\
	   	src/execute_redirection.c\
	   	src/execute_redirection2.c\
	   	src/execute_simple_cmd.c\
	   	src/ft_cd.c\
	   	src/ft_cd_env.c\
	   	src/ft_change_arg.c\
	   	src/main.c\
	   	src/path_checker.c\
	   	src/sh_execution.c\
	   	src/sh_loop.c\
	   	src/tools.c\
	   	src/tools2.c\
		src/ft_expanitions.c\
		src/free_ast.c\
		src/parser/check_quotes.c\
	   	src/parser/check_syntax.c\
	   	src/parser/parse_types.c\
	   	src/parser/parser.c\
	   	src/parser/tokenz.c\
	   	src/parser/tokenz_checker.c\
		src/parser/tokenz_checker2.c\
		src/hash.c\


OBJS    = $(SRCS:.c=.o)


NAME		= 21sh
CC = gcc
CFLAGS		= -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	gcc -g -ltermcap $(CFLAG) $(OBJS) libft/libft.a -o $(NAME)

clean :
	rm -rf $(OBJS) 
	@make -C libft clean

fclean : clean
	rm -rf $(NAME)
	@make -C libft fclean

re : fclean all
