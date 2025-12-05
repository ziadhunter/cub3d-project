CC = cc
CFLAGS = -Wall -Werror -Wextra
CMLX = -lmlx -lXext -lX11 -lm

SRC = cub3d.c \
	laboratoire/parsing/extract_element_utils.c \
	laboratoire/parsing/extract_element.c \
	laboratoire/parsing/free_function.c \
	get_next_line/get_next_line.c \
	laboratoire/parsing/initialization.c \
	laboratoire/parsing/parsing_the_map.c \
	laboratoire/parsing/parsing_utils.c \
	laboratoire/parsing/parsing.c \
	get_next_line/get_next_line_utils.c

NAME = cub3d
OBJECT = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECT) libft/libft.a $(CMLX) -o $(NAME)

bonus: $(NAME_BONUS)


cv: map_convert.o
	$(CC) $^ $(CMLX) -o $@
clean:
	rm -f $(OBJECT) $(OBJECT_BONUS)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: clean fclean all re bonus


# CC = cc
# CFLAGS = -Wall -Werror -Wextra
# CMLX = -lmlx -lXext -lX11 -lm

# SRC = cub3d.c \
# 	laboratoire/parsing/extract_element_utils.c \
# 	laboratoire/parsing/extract_element.c \
# 	laboratoire/parsing/free_function.c \
# 	get_next_line/get_next_line.c \
# 	laboratoire/parsing/initialization.c \
# 	laboratoire/parsing/parsing_the_map.c \
# 	laboratoire/parsing/parsing_utils.c \
# 	laboratoire/parsing/parsing.c \
# 	get_next_line/get_next_line_utils.c

# NAME = cub3d
# OBJECT = $(SRC:%.c=%.o)

# all: $(NAME)

# $(NAME): $(OBJECT) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJECT) libft/libft.a $(CMLX) -o $(NAME)

# bonus: $(NAME_BONUS)

# clean:
# 	rm -f $(OBJECT) $(OBJECT_BONUS)
# 	$(MAKE) clean -C libft

# fclean: clean
# 	rm -f $(NAME) $(NAME_BONUS)
# 	$(MAKE) fclean -C libft

# re: fclean all

# .PHONY: clean fclean all re bonus


CC = cc
CFLAGS = -Wall -Werror -Wextra
CMLX = -lmlx -lXext -lX11 -lm
SRC = mini_map_test.c

NAME = cub3d
OBJECT = $(SRC:%.c=%.o)

all:  $(NAME)

$(LIBFT) :
	make -C libft

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(SRC) libft/libft.a $(CMLX) -o $(NAME) 

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJECT) $(OBJECT_BONUS)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: clean fclean all re bonus
