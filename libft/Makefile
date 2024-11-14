NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
SOURCE = libft_base/ft_atoi.c libft_base/ft_itoa.c libft_base/ft_strdup.c libft_base/ft_strlcpy.c \
		 libft_base/ft_strlen.c libft_base/ft_strncmp.c libft_base/ft_toupper.c \
		 ft_printf/ft_printf.c ft_printf/handle_char.c ft_printf/handle_dec.c ft_printf/handle_hex.c \
		 ft_printf/handle_int.c ft_printf/handle_point.c ft_printf/handle_str.c ft_printf/hex_functions.c

OBJ = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) *.a

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
