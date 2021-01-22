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
	@make clean
	@$(CC) $(FLAGS) $(FLAG_SQL) $(DEBUG_FLAGS) $(OBJ) -o ../$(NAME)
$(OBJ): | obj
obj: 
	@mkdir $@
	
obj/%.o: src/%.c $(INC) 
ifeq ($< ,src/db.c)
		@$(CC) $(FLAGS) $(FLAG_SQL) -c $< -o $@
else
		@$(CC) $(FLAGS) -c $< -o $@
endif
clean:
	@rm -rf *.o
uninstall: clean
	@rm -rf ./obj
	@rm -rf ../$(NAME)
reinstall: uninstall all