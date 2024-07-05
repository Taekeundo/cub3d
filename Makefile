###   [ VARIABLE SETTING ]   ###
# Name of the executing file.
NAME	= cub3D

# Sort of the compiler and flags.
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# Directory of the libraries (libft & mlx42).
LIBFT	= ./libft
LIBMLX	= ./MLX42

# To include header files (header file's path)
HEADERS	= -I ./include -I $(LIBFT) -I $(LIBMLX)/include/MLX42

# To link libraries to the executing file.
LIBX	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBF	= $(LIBFT)/libft.a

# Find all *.c files in ./src directory
SRCS	= $(shell find ./src -iname "*.c")

# Directory for object files
OBJ_DIR	= ./obj

# Convert source file to object file and save those object lists.
OBJS	= $(SRCS:./src/%.c=$(OBJ_DIR)/%.o)

###   [ TARGET SETTING ]   ###
# Main target to compile
all: $(NAME)

# Clone the mlx library from the github and build it.
libmlx:
	@if ! [ -d "./MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
		cd $(LIBMLX); cmake -B build ; cmake --build build -j4; \
	fi

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile all (*.c) files to (*.o) files.
$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# Ensure libft is built before linking
$(LIBF):
	make -C $(LIBFT)

# Creates an executable file by linking (LIBMLX)library, (LIBFT)library and (OBJECT)files.
$(NAME): libmlx $(OBJS) $(LIBF)
	@$(CC) $(OBJS) $(LIBX) $(LIBF) $(HEADERS) -o $(NAME)
	@echo "$(NAME) built successfully"

# Delete object files
clean:
	@rm -f $(OBJS)
	make clean -C $(LIBFT)
	@echo "Object files deleted"

# Run 'clean' and delete $(NAME): executable file and $(LIBFT): library file.
fclean: clean
	@rm -f $(NAME)
	make fclean -C $(LIBFT)
	@rm -rf $(OBJ_DIR)
	@echo "Executable and object directory deleted"

# Run 'fclean' and 'all'
re: fclean all

# Indicates that targets are commands rather than actual files.
.PHONY: all clean fclean re libmlx
