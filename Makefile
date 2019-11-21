CC := g++
NAME := upgma
OBJ := $(NAME).cpp
CPPFLAGS := 

$(NAME):
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(NAME)