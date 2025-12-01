CC = cc -g3
# CFLAGS = -Wall -Werror -Wextra -g3
CMLX = -lmlx -lXext -lX11 -lm
SRC_BONUS = mini_map_test.c creat_rays.c mini_map.c load_textures.c map_convert.c door_check.c
#SRC_BONUS = maintest.c
NAME_BONUS = cub3d
OBJECT_BONUS = $(SRC_BONUS:%.c=%.o)

all:  $(NAME_BONUS)

$(NAME_BONUS) : $(OBJECT_BONUS) 
	$(CC) $(SRC_BONUS) $(CMLX) -o $(NAME_BONUS)


cv: map_convert.o
	$(CC) $^ $(CMLX) -o $@

clean:
	rm -f $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

run: all
	# clear
	./$(NAME_BONUS)
	make fclean

gdb: all
	clear
	valgrind ./$(NAME_BONUS)
	make fclean

git: fclean
	@echo "Enter commit message: "; \
	read var; \
	git add .; \
	git commit -m "$$var"; \
	git push



.PHONY: clean fclean all re bonus
	