# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/07 13:07:53 by mchardin          #+#    #+#              #
#    Updated: 2021/02/03 15:33:38 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./srcs/

INCLUDES	=	./includes/

SRCS		=	$(addprefix $(PREFIX), \
								ft_philo.c \
								ft_print.c \
								ft_life.c \
								ft_utils.c \
								ft_atoi.c \
								ft_calloc.c \
								ft_isposnumber.c \
								ft_strcpyphilo.c \
								)

OBJS		=	${SRCS:.c=.o}

DEPS		=	${OBJS:.o=.d}

CC			=	clang-9

CFLAGS		=	-pthread -Werror -Wextra -Wall -I ${INCLUDES} -MMD

NAME 		=	philo_two

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME) 5 800 200 200

clean:
			${RM} ${OBJS}
			${RM} ${DEPS}

fclean:
			${RM} ${OBJS}
			${RM} ${DEPS}
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all re run clean fclean

-include	${DEPS}