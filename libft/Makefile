# DEFINE
NAME		=	libft.a

# EXECUTION
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM		=	rm -rf
AR		=	ar rcs

# SOURCE
SRCS		=	src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putnbr_fd.c src/ft_putendl_fd.c \
			src/ft_striteri.c src/ft_strlen.c src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c \
			src/ft_isascii.c src/ft_isprint.c src/ft_memset.c  src/ft_bzero.c src/ft_memcpy.c \
			src/ft_memmove.c src/ft_strlcat.c src/ft_tolower.c src/ft_toupper.c src/ft_strchr.c \
			src/ft_strrchr.c src/ft_strncmp.c src/ft_strlcpy.c src/ft_memchr.c src/ft_memcmp.c \
			src/ft_strnstr.c src/ft_atoi.c src/ft_calloc.c src/ft_strdup.c src/ft_substr.c \
			src/ft_strjoin.c src/ft_strtrim.c src/ft_split.c src/ft_itoa.c src/ft_strmapi.c \
			src/ft_strcmp.c src/ft_isspace.c src/ft_free_array.c \

B_SRCS		=	src/ft_lstnew.c src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c \
			src/ft_lstadd_back.c src/ft_lstdelone.c src/ft_lstiter.c src/ft_lstclear.c src/ft_lstmap.c \

# Directory for object files
OBJ_DIR		=	obj

# Convert source file to object file and save those object lists.
OBJS		=	$(SRCS:src/%.c=$(OBJ_DIR)/%.o)
B_OBJS		=	$(B_SRCS:src/%.c=$(OBJ_DIR)/%.o)

# MAIN COMMAND
all:		$(NAME)

$(NAME):	$(OBJS)
		@$(AR) $(NAME) $(OBJS)
		
bonus:		$(OBJS) $(B_OBJS)
		@$(AR) $(NAME) $(OBJS) $(B_OBJS)

# Create object directory if it doesn't exist
$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

# Compile all (*.c) files to (*.o) files.
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(OBJ_DIR)

re:		fclean all

.PHONY: all clean fclean re bonus
