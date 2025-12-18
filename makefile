CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
CMLX = -lmlx -lXext -lX11 -lm

INCLUDE = includes
MAP_NAME = full_map

SRC = cub3d.c \
	src/utils/file.c src/utils/tan.c \
	src/parsing/extract_element_utils.c \
	src/parsing/extract_element.c \
	src/parsing/free_function.c \
	src/parsing/initialization.c \
	src/parsing/parsing_the_map.c \
	src/parsing/parsing_utils.c \
	src/parsing/parsing.c \
	src/the_game/load_game.c \
	src/the_game/load_weapons_data.c \
	src/the_game/map_convert.c \
	src/the_game/projection_utils.c \
	src/the_game/player_movement.c \
	src/the_game/dlist.c \
	src/the_game/the_game.c \
	src/the_game/door_check.c \
	src/the_game/door_check_utils.c \
	src/the_game/door_movement.c \
	src/the_game/mini_map.c src/the_game/mini_map_utils.c \
	src/the_game/initialization.c src/the_game/free_and_exit.c \
	src/the_game/key_mouvement.c src/the_game/key_mouvement_utils.c src/the_game/key_movement_utils2.c \
	src/the_game/ray_casting.c \
	src/the_game/ray_casting_utils.c \
	src/the_game/ray_casting_utils2.c \
	src/the_game/ray_casting_utils3.c \
	src/the_game/projaction.c \
	src/libft/get_next_line/get_next_line.c \
	src/libft/get_next_line/get_next_line_utils.c \
	src/the_game/mouse_event.c \
	src/the_game/knife_rendring.c


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

run: re
	clear
	./$(NAME) maps/good/$(MAP_NAME).cub
	make fclean

gdb: all
	clear
	valgrind --leak-check=full -s ./$(NAME) maps/good/$(MAP_NAME).cub
	make fclean

git: fclean
	@echo "Enter commit message: "; \
	read var; \
	git add .; \
	git commit -m "$$var"; \
	git push

valtest: re
	clear
	valgrind --suppressions=supp.supp --leak-check=full --track-fds=yes --track-origins=yes -s ./$(NAME) maps/good/$(MAP_NAME).cub
	make fclean > /dev/null

.PHONY: clean fclean all re bonus
