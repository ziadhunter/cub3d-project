# CC = cc
# # CFLAGS = -Wall -Werror -Wextra -g3
# CMLX = -lmlx -lXext -lX11 -lm
# # SRC_BONUS = mini_map_test.c creat_rays.c mini_map.c
# SRC_BONUS = parsing/start.c
# #SRC_BONUS = maintest.c
# NAME_BONUS = test
# OBJECT_BONUS = $(SRC_BONUS:%.c=%.o)

# all:  $(NAME_BONUS)

# $(LIBFT) :
# 	make -C libft

# $(NAME_BONUS) : $(OBJECT_BONUS) $(LIBFT)
# 	$(CC) $(SRC_BONUS) $(CMLX)  $(LIBFT) -o $(NAME_BONUS)

# clean:
# 	rm -f $(OBJECT) $(OBJECT_BONUS)

# fclean: clean
# 	rm -f $(NAME) $(NAME_BONUS)

# re: fclean all

# .PHONY: clean fclean all re bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CMLX = -lmlx -lXext -lX11 -lm

# paths
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ./gnl
GNL_SRC = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SRC = parsing/start.c $(GNL_SRC)
OBJ = $(SRC:.c=.o)

NAME = test

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(CMLX) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
