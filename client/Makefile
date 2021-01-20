CC = clang

NAME = uchat
INC = inc/*.h
SRC := $(wildcard src/*.c)
OBJ := $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
DEBUG_FLAGS = -fsanitize=address -fno-omit-frame-pointer
GTK_FLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJ)
	@make clean
	@$(CC) $(FLAGS) $(GTK_LIBS) $(DEBUG_FLAGS) $(OBJ) -o ../$(NAME)

$(OBJ): | obj

obj:
	@mkdir $@

obj/%.o: src/%.c $(INC)
	@$(CC) $(FLAGS) $(GTK_FLAGS) -c $< -o $@

clean:
	@rm -rf *.o

uninstall: clean
	@rm -rf ./obj
	@rm -rf ../$(NAME)

reinstall: uninstall all
