#      ___         ___           ___     
#     /\  \       /\  \         /\__\    	POC PROJECT
#    /::\  \     /::\  \       /:/  /    	Makefile - XOR	
#   /:/\:\__\   /:/\:\  \     /:/  /     	
#  /:/ /:/  /  /:/  \:\  \   /:/  /  ___ 
# /:/_/:/  /  /:/__/ \:\__\ /:/__/  /\__\
# \:\/:/  /   \:\  \ /:/  / \:\  \ /:/  /
#  \::/__/     \:\  /:/  /   \:\  /:/  / 
#   \:\  \      \:\/:/  /     \:\/:/  /  
#    \:\__\      \::/  /       \::/  /   
#     \/__/       \/__/         \/__/


NAME = Cryptor
OBJ = $(SRC:.c=.o)
GCC = gcc
INCLUDE = include
CFLAGS = -I$(INCLUDE)
RM = rm -f
SRC =	src/cypher.c		\
		src/one_time_pad.c

all: $(NAME)

$(NAME):    $(OBJ)
			$(GCC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re :		fclean all
