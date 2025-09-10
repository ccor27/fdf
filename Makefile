NAME= fdf
LIBFT_DIR= libft
LIBFT= $(LIBFT_DIR)/libft.a
MINILIBX_DIR= minilibx-linux
MINILIBX=$(MINILIBX_DIR)/libmlx.a

INCLUDES= -I. -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

SRC_FILES = error_handler.c fdf.c parse_and_store_utils.c \
        parse_and_store.c calculations.c draw.c hooks.c

SRC_BONUS_FILES = calculations_bonus.c draw_bonus.c cleanup_bonus.c \
                    hooks_bonus.c parse_and_store_bonus.c parse_and_store_utils_bonus.c \
                    fdf_bonus.c draw_utils_bonus.c

OBJ_DIR= obj
OBJ_BONUS_DIR = obj_bonus

SRC= $(addprefix src/,$(SRC_FILES))
SRC_BONUS= $(addprefix bonus/,$(SRC_BONUS_FILES))

OBJ= $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
OBJ_BONUS= $(addprefix $(OBJ_BONUS_DIR)/,$(SRC_BONUS_FILES:.c=.o))

CFLAGS = -Wall -Wextra -Werror
LFLAGS= -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm
CC = gcc

#make ; valgrind --leak-check=full --show-leak-kinds=all ./fdf test_maps/42.fdf
define LOADING_BAR_COMP_MINILIBX
	@printf "\033[0;32mCompiling minilibx: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

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

all: $(NAME)

$(NAME): $(OBJ) $(MINILIBX)
	@$(MAKE) -C $(LIBFT_DIR) --silent
	$(call LOADING_BAR_COMP)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

bonus: $(OBJ_BONUS) $(MINILIBX)
	@$(MAKE) -C $(LIBFT_DIR) --silent
	$(call LOADING_BAR_COMP_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# $(MINILIBX):
# 	@$(MAKE) -C $(MINILIBX_DIR) --silent
$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR) > /dev/null 2>&1
	$(call LOADING_BAR_COMP_MINILIBX)

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
	@$(MAKE) -C $(MINILIBX_DIR) clean > /dev/null 2>&1
#	@$(MAKE) -C $(MINILIBX_DIR) clean --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@rm -f $(MINILIBX_DIR)/libmlx.a > /dev/null 2>&1
#	@rm -f $(MINILIBX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re bonus
