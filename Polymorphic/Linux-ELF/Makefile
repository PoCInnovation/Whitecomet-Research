
SRC	=	src/main.c	\
		src/ELF/change_sec_perm.c \
		src/ELF/find_section.c 	\

OBJ	=	$(SRC:.c=.o)

NAME	=	PoCrypt

CC	=	gcc -o

CFLAGS	+=	-Wall -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean clean all re
