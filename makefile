CC = cc
CFLAGS = -Wall -Werror -Wextra
CMLX = -lmlx -lXext -lX11 -lm

INCLUDE = includes

SRC = cub3d.c \
	src/parsing/extract_element_utils.c \
	src/parsing/extract_element.c \
	src/parsing/free_function.c \
	src/parsing/initialization.c \
	src/parsing/parsing_the_map.c \
	src/parsing/parsing_utils.c \
	src/parsing/parsing.c \
	src/the_game/the_game.c \
	src/the_game/mini_map.c src/the_game/mini_map_utils.c \
	src/the_game/initialization.c src/the_game/free_and_exit.c\
	src/the_game/key_mouvement.c src/the_game/key_mouvement_utils.c\
	src/the_game/ray_casting.c \
	src/the_game/ray_casting_utils.c \
	src/the_game/projaction.c \
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c


LIBFT = src/libft/libft.a
NAME = cub3d
OBJECT = $(SRC:%.c=%.o)

all: $(NAME)

$(LIBFT) :
	make -C src/libft

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECT) -I./$(INCLUDE) $(LIBFT) $(CMLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./$(INCLUDE) -c $< -o $@

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJECT) $(OBJECT_BONUS)
	$(MAKE) clean -C src/libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C src/libft

re: fclean all

.PHONY: clean fclean all re bonus
