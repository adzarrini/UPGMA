CC := g++
NAME := upgma
RANDOM := gen-dm
OBJ := $(NAME).cpp
CPPFLAGS := 

all: $(NAME) $(RANDOM)

$(NAME):
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS)

$(RANDOM):
	$(CC) $(RANDOM).cpp -o $(RANDOM) $(CPPFLAGS)

clean:
	$(RM) $(NAME) $(RANDOM)
