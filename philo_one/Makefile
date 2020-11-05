# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/07 13:07:53 by mchardin          #+#    #+#              #
#    Updated: 2020/11/05 18:07:34 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./srcs/

INCLUDES	=	./includes/

INCL_FILES	=	$(addprefix $(INCLUDES), ft_philo.h)

SRCS		=	$(addprefix $(PREFIX), \
								ft_philo.c \
								ft_print.c \
								ft_life.c \
								ft_utils.c \
								ft_atoi.c \
								ft_calloc.c \
								ft_isposnumber.c \
								ft_itoa.c \
								ft_putnbrphilo.c \
								)

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

CFLAGS		=	-pthread -Werror -Wextra -Wall -I ${INCLUDES}

NAME 		=	philo_one

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS} ${INCL_FILES}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME) 70 3110 100 100

clean:
			${RM} ${OBJS}

fclean:
			${RM} ${OBJS}
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all re run clean fclean
