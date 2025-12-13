NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

FILES := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

PRINTF_SRC := ft_printf/ft_printf_bonus.c \
	ft_printf/src_bonus/number_2_bonus.c ft_printf/src_bonus/more_bonus.c \
	ft_printf/src_bonus/ft_putchar_bonus.c ft_printf/src_bonus/printing_funcs_bonus.c \
	ft_printf/src_bonus/writer_bonus.c ft_printf/src_bonus/options_bonus.c ft_printf/src_bonus/print_all_bonus.c \
	ft_printf/src_bonus/print_plus_bonus.c ft_printf/src_bonus/converter_bonus.c \
	ft_printf/src_bonus/calculate_width_precision_bonus.c

GNL_SRC := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

BONUS_FILES := ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c

OBJ_FILES := $(FILES:.c=.o)
BONUS_OBJ := $(BONUS_FILES:.c=.o)
PRINTF_OBJ := $(PRINTF_SRC:.c=.o)
GNL_OBJ := $(GNL_SRC:.c=.o)


$(NAME): $(OBJ_FILES)
	ar rcs $@ $^

bonus: $(BONUS_OBJ) $(OBJ_FILES)
	ar rcs $(NAME) $^

printf: $(PRINTF_OBJ)
	ar rcs $(NAME) $^

gnl: $(GNL_OBJ)
	ar rcs $(NAME) $^

all: $(NAME) bonus printf gnl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re
.SECONDARY: $(OBJ_FILES) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
