NAME = Air-Hockey
CLANG = clang++ -std=c++14
INC = -I ./includes -I /usr/local/include/SDL2
LIB = -L /usr/local/lib -lSDL2

LIST =	Main \
		Field \
		Paddle \
		Ball

SRC =	$(addprefix src/, $(addsuffix .cpp, $(LIST)))
OBJ =	$(addprefix obj/, $(addsuffix .o, $(LIST)))

obj/%.o: src/%.cpp
	@$(CLANG) -c $< -o $@ $(INC) 

all: $(NAME)

$(NAME): $(OBJ)
	@$(CLANG) $(OBJ) -o $(NAME) $(LIB)

clean:
	@rm $(OBJ)

fclean: clean
	@rm $(NAME)

re: fclean all

install:
	@sudo apt-get install libsdl2-dev
