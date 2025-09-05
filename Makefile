NAME= fdf
LIBFT= libft/libft.a

SRC_FILES = error_handler.c fdf.c parse_and_store_utils.c \
		parse_and_store.c calculations.c draw.c hooks.c

SRC_BONUS_FILES = calculations_bonus.c draw_bonus.c error_handler_bonus.c \
					hooks_bonus.c parse_and_store_bonus.c parse_and_store_utils_bonus.c \
					fdf_bonus.c

OBJ_DIR= obj
OBJ_BONUS_DIR = obj_bonus

SRC= $(addprefix src/,$(SRC_FILES))
SRC_BONUS= $(addprefix bonus/,$(SRC_BONUS_FILES))

OBJ= $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
OBJ_BONUS= $(addprefix $(OBJ_BONUS_DIR)/,$(SRC_BONUS_FILES:.c=.o))

CFLAGS = -Wall -Wextra -Werror
CC = gcc

#make ; valgrind --leak-check=full --show-leak-kinds=all ./fdf test_maps/42.fdf
define LOADING_BAR_COMP
	@printf "\033[0;32mCompiling fdf: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

define LOADING_BAR_COMP_BONUS
	@printf "\033[0;32mCompiling fdf bonus: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

define LOADING_BAR_CLEAN
	@printf "\033[0;31mCleaning objects: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

#paths
LIBFT_DIR= libft
INCLUDES= -I. -I$(LIBFT_DIR)
LFLAGS= -L./minilibx -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJ)
		@$(MAKE) -C $(LIBFT_DIR) --silent
		$(call LOADING_BAR_COMP)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

bonus: $(OBJ_BONUS)
		@$(MAKE) -C $(LIBFT_DIR) --silent
		$(call LOADING_BAR_COMP_BONUS)
		@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@(MAKE) -C libft

$(OBJ_DIR)/%.o : src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR)/%.o : bonus/%.c | $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	$(call LOADING_BAR_CLEAN)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent

re: fclean all

.PHONY: all clean fclean re bonus
