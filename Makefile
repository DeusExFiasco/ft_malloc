CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -fPIC
LDFLAGS = -shared

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LIB = libft/libft.a
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC_FILES:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIB)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@rm -f libft/libft.a
	@printf "$(GREEN)Cleaned object files$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)Cleaned everything$(RESET)\n"

re: fclean all

reclean: re .FORCE
	@$(MAKE) clean

allclean: all .FORCE
	@$(MAKE) clean

.PHONY: all clean fclean re reclean allclean .FORCE