CC = clang

NAME = uchat_server
INC = inc/*.h
SRC := $(wildcard src/*.c)
OBJ := $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
FLAG_SQL = -lsqlite3
DEBUG_FLAGS = -fsanitize=address -fno-omit-frame-pointer


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(FLAG_SQL) $(DEBUG_FLAGS) $(OBJ) -o ../$(NAME)
	@make clean
	@mkdir db
	@mkdir log
	@printf "\r\33[2K$(NAME):\t\t \033[32;1mcreated\033[0m\n"
$(OBJ): | obj
obj:
	@mkdir $@

obj/%.o: src/%.c $(INC)
ifeq ($< ,src/db.c)
		@$(CC) $(FLAGS) $(FLAG_SQL) -c $< -o $@
else
		@$(CC) $(FLAGS) -c $< -o $@
endif
	@printf "\r\33[2K$(NAME):\033[33;1m\t\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"
clean:
	@rm -rf obj/*.o
	@rm -rf ./obj
	@rm -rf ./db
	@rm -rf ./log
	@printf "$(NAME):\t\t \033[31;1mdeleted\033[0m $(OBJ_DIR)\r"

uninstall:
	@rm -rf ../$(NAME)
	@printf "$(NAME):\t\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all






 # 
 # Dorabotat` napil`nikom.
 # 15.02.2021
 # Odarchenko M. S. 
 # Asemiletov A. I.
 # Kuleshova D. A. 
 # Botezat V. K.
 # Ivanov M. M.
 # 
 #

