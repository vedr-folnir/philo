NAME = philo
CC = cc
FLAGS = -pthread -Wall -Wextra -Werror -g3
SRCS =	philosophers.c \
		errors.c \
		threads.c \
		utils.c \
		get_data.c \

OBJ := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJ}
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) 

all: ${NAME}

clean:
	rm -f *.o */*.o */*/*.o

fclean: clean
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re

