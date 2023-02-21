# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:46:42 by jhwang2           #+#    #+#              #
#    Updated: 2023/02/21 11:14:27 by jhwang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-I ./pipex.h
SRCS		=	pipex.c\
				cmd.c\
				close.c\
				do_execve.c\
				free.c\
				ft_function1.c\
				ft_function2.c\
				ft_split.c
OBJS		=	$(SRCS:.c=.o)
BONUS_SRCS	=	pipex_bonus.c\
				cmd_bonus.c\
				close_bonus.c\
				do_execve_bonus.c\
				free_bonus.c\
				ft_function1_bonus.c\
				ft_function2_bonus.c\
				ft_split_bonus.c
BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)
CC			=	CC
RM			=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus