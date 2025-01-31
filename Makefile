include colors.mk
NAME = connect4

all: $(NAME)

SOURCE_DIR = src
LIBFT_DIR = $(SOURCE_DIR)/libft
BUILD_DIR = build

CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -g #-Wpedantic
# CFLAGS += -g -Og -fsanitize=address,undefined,leak

LIBFT = $(LIBFT_DIR)/libft.a

$(LIBFT):
	@make -C $(LIBFT_DIR) all

FILENAMES += \
	main.c

FILENAMES += \
	get_next_line/get_next_line.c

SRC = $(addprefix $(SOURCE_DIR)/,$(FILENAMES))
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(BUILD_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -MMD -c $< -o $@

-include $(DEP)

clean:
	rm -fr $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# valgrind:
# 	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) resources/scene_descriptions/01_test.cub

.PHONY: all lft clean fclean re