CC = clang

NAME = uchat_server
INC = inc/*.h
SRC := $(wildcard src/*.c)
OBJ := $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
DEBUG_FLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(DEBUG_FLAGS) $(OBJ) -o ../$(NAME)
	@make clean
	@printf "\r\33[2K$(NAME):\t \033[32;1mcreated\033[0m\n"

$(OBJ): | obj

obj:
	@mkdir $@

obj/%.o: src/%.c $(INC)
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r\33[2K$(NAME):\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

clean:
	@rm -rf obj/*.o
	@rm -rf ./obj
	@printf "$(NAME):\t \033[31;1mdeleted\033[0m $(OBJ_DIR)\r"

uninstall:
	@rm -rf ../$(NAME)
	@printf "$(NAME):\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all
