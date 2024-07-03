###   [ VARIABLE SETTING ]   ###
# Name of the executing file.
NAME	= cub3D

# Sort of the compiler and flags.
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
# -Wall		: 모든 경고 메시지를 활성화.
# -Wextra	: 추가적인 경고 메시지 활성화.
# -Werror	: 경고를 에러로 취급, 컴파일 중단.

# Directory of the libraries (libft & mlx42).
LIBFT	= ./libft
LIBMLX	= ./MLX42

# To include header files (header file's path)
HEADERS	= -I ./include -I $(LIBFT) -I $(LIBMLX)/include/MLX42

# To link libraries to the executing file.
LIBX	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBF	= $(LIBFT)/libft.a
# Static library
#	Compile time에 library가 링크(실행 파일에 포함)되는 방식
#	(ex) $(LIBMLX)/build/libmlx42.a, $(LIBFT)/libft.a
#
# Dynamic library
#	Run time에 참조(동적으로 로드)되며, 메모리 효율적이나, 배포가 복잡하다.
#	-ldl		: Library of Dynamical Loading
#				  동적 로딩 기능 제공: dlopen, dlsym, dlclose.
#	-lglfw		: Library of GLFW.
#				  윈도우 생성, 키보드, 마우스 입력 처리 제공: 게임 개발, 시뮬레이션
#	-pthread	: Library of POSIX thread.
#				  멀티스레딩 제공: 병렬 처리, 동시성 프로그래밍을 구현, pthread_create, pthread_join, pthread_mutex_lock
#	-lm			: Librart of Math.
#				  수학 함수 제공: sin, cos, sqrt, exp

# Find all *.c files in ./src directory
SRCS	= $(shell find ./src -iname "*.c")

# Convert source file to object file and save those object lists.
OBJS	= $(SRCS:.c=.o)

###   [ TARGET SETTING ]   ###
# Main target to compile
all: $(NAME)

# Clone the mlx library from the github and build it.
libmlx:
	@if ! [ -d "./MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
		cd $(LIBMLX); cmake -B build ; cmake --build build -j4; \
	fi
# STEP(1): If the directory (MLX42) doesn't exist, then execute this command.
# STEP(2): Clone MLX42 from the github.
# STEP(3): Build the library.
# "if ... then ... fi": Shell script phrase // if block starts and ends
# @: Option, when we use, not want to print message.

# Compile all (*.c)files to (*.o)files.
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"
# &&: 앞 명령어가 성공적으로 실행된 경우에만 뒤 명령어 실행.
# printf "Compiling: $(notdir $<)" // 현재 컴파일 중인 파일의 이름을 출력 (파일 경로는 제외)

# Creates an execututable file by linking (LIBMLX)library, (LIBFT)library and (OBJECT)files.
$(NAME): libmlx $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBX) $(LIBF) $(HEADERS) -o $(NAME)
# $(CC)				: Call the compiler (ex) cc, gcc
# $(CLFAGS)			: Add flags for the compiler (ex) -Wextra -Wall -Werror
# $(OBJS)			: Include object files, which is already compiled.
# $(LIBX), $(LIBF)	: Link libraries.
# $(HEADERS)		: Specifies the header file path.
# -o $(NAME)		: Specifies the name of the executing file.

# Delete object file
clean:
	@rm -f $(OBJS)
	make clean -C $(LIBFT)

# Run 'clean' and delete $(NAME): executable file and $(LIBFT): library file.
fclean: clean
	@rm -f $(NAME)
	make fclean -C $(LIBFT)

# Run 'fcelan' and 'all'
re: fclean all

# Indicates that targets are commands rather than actual files.
.PHONY: all clean fclean re libmlx