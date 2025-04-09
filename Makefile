################################################################################
#                                                                              #
#                                    MAKEFILE                                  #
# Project:     pipex                                                           #
# Created:     12/11/2024                                                      #
# Author:      kixk                                                            #
#                                                                              #
################################################################################

################################################################################
###############                     BUILD SETUP                  ###############
################################################################################

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -Iinclude
LIB = libft/libft.a

################################################################################
###############                     DIRECTORIES                  ###############
################################################################################

SRC_DIR = src

################################################################################
###############                    SOURCE FILES                  ###############
################################################################################

SOURCE = pipex.c child_utils.c error_handling.c parsing_utils.c

MAIN_SRC := $(addprefix $(SRC_DIR)/, $(SOURCE))

OBJ = $(MAIN_SRC:.c=.o)

################################################################################
###############                 COMPILATION RULES                ###############
################################################################################

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIB)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re