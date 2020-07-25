
SRC	=	src/main.c	\
		src/gen_bytes.c	\
		src/replace_bytes.c	\
		src/ELF/change_sec_perm.c \
		src/ELF/find_section.c 	\

OBJ	=	$(SRC:.c=.o)

NAME	=	PoCrypt

CC	=	gcc -o

CFLAGS	+= -Wall -masm=intel -I./include

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
