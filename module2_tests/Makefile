CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -lpthread
NAME = mod_two
OBJS = OBJ = $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
INCS = inc/*.h
SRCS = src/*.c
TARGET = MOD_TWO
DEBUG_FLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(TARGET) clean

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJ) -o $(NAME) $(SRCS)

$(OBJ): | obj

obj:
	@mkdir obj

obj/%.o: src/%.c $(INC)
	@clang $(FLAGS) -c $< -o $@

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf *.o

reinstall: uninstall clean all
