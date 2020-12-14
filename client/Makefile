CC = clang

NAME = client
INC = inc/*.h
SRC := $(wildcard src/*.c)
OBJ := $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
DEBUG_FLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(NAME)

$(NAME): $(OBJ)
	@make clean
	@$(CC) $(FLAGS) $(DEBUG_FLAGS) $(OBJ) -o $(NAME)
$(OBJ): | obj
obj: 
	@mkdir $@
obj/%.o: src/%.c $(INC) 
	@$(CC) $(FLAGS) -c $< -o $@
clean:
	@rm -rf *.o
uninstall: clean
	@rm -rf ./obj
	@rm -rf $(NAME)
reinstall: uninstall all