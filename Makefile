PREFIX		=	./srcs/

INCLUDES	=	./includes/

INCL_FILES	=	$(addprefix $(INCLUDES), philo.h)

SRCS		=	$(addprefix $(PREFIX), \
								ft_philo.c \
								)

OBJS		=	${SRCS:.c=.o}

CC			=	clang-9

CFLAGS		=	-Werror -Wextra -Wall -I ${INCLUDES}

NAME 		=	philo_

RM			=	rm -f

all:		
			${MAKE} ${NAME}

${NAME}:	${OBJS} ${INCL_FILES}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME)

clean:
			${RM} ${OBJS}

fclean:
			${RM} ${OBJS}
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all re run clean fclean
