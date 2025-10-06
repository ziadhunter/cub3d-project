CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
CMLX = -lmlx -lXext -lX11 -lm
SRC_BONUS = mini_map_test.c 
#SRC_BONUS = maintest.c
NAME_BONUS = test
OBJECT_BONUS = $(SRC_BONUS:%.c=%.o)

all:  $(NAME_BONUS)

$(NAME_BONUS) : $(OBJECT_BONUS) 
	$(CC) $(SRC_BONUS) $(CMLX) -o $(NAME_BONUS)

clean:
	rm -f $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re bonus
	