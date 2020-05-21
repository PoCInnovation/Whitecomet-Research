
SRC	=	src/PE.c	\
		src/main.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	PoCrypt-PE

CC	=	gcc -o

CFLAGS	+=	-Wall -Wextra -Werror

CPPFLAGS	+= -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean clean all re
