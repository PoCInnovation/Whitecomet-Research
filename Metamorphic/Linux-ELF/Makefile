
SRC	=	src/main.c \
		src/gen_bytes.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	PoCrypt

CC	=	gcc -o

CPPFLAGS	+= -Wall -masm=intel -I./include

LDFLAGS		+= -lm -lkeystone

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean clean all re
