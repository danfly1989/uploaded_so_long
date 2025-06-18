NAME_SO_LONG = so_long

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC_SO_LONG = \
	src/main.c src/map.c src/player.c src/movement.c src/doodling.c src/validation.c src/validate_map.c src/management.c

OBJ_SO_LONG = $(SRC_SO_LONG:.c=.o)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS = -lft -lmlx -lm -lXext -lX11 -lpthread -lrt -ldl

.PHONY: all clean fclean re debug check-deps

# Default target - must be first rule
all: check-deps $(NAME_SO_LONG)

check-deps:
	@echo "Checking dependencies..."
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX directory not found, will clone it..."; \
	fi
	@if [ ! -f "$(LIBFT)" ]; then \
		echo "libft not found, will build it..."; \
	fi

# Clone MiniLibX if not already present
$(MLX_DIR):
	@echo "Cloning MiniLibX..."
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)
	@echo "MiniLibX cloned successfully"

$(LIBFT):
	@echo "Building libft..."
	make -C $(LIBFT_DIR)

$(MLX_LIB): | $(MLX_DIR)
	@echo "Building MiniLibX..."
	@echo "Checking if required packages are installed..."
	@if ! pkg-config --exists x11 xext; then \
		echo "Error: X11 development libraries not found."; \
		echo "On Rocky Linux, install with: sudo dnf install libX11-devel libXext-devel"; \
		echo "On Ubuntu, install with: sudo apt-get install libx11-dev libxext-dev"; \
		exit 1; \
	fi
	make -C $(MLX_DIR)
	@echo "MiniLibX built successfully"

$(NAME_SO_LONG): $(OBJ_SO_LONG) $(LIBFT) $(MLX_LIB)
	@echo "Linking $(NAME_SO_LONG)..."
	$(CC) $(CFLAGS) $(OBJ_SO_LONG) -o $@ $(LDFLAGS) $(LDLIBS)

src/%.o: src/%.c | $(MLX_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	[ -d $(MLX_DIR) ] && make -C $(MLX_DIR) clean || true
	rm -f $(OBJ_SO_LONG)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME_SO_LONG)

re: fclean all

debug:
	@echo "=== Debug Information ==="
	@echo "Operating system: $(uname -s)"
	@echo "MLX_DIR exists: $(test -d $(MLX_DIR) && echo 'YES' || echo 'NO')"
	@echo "MLX_LIB exists: $(test -f $(MLX_LIB) && echo 'YES' || echo 'NO')"
	@echo "LIBFT exists: $(test -f $(LIBFT) && echo 'YES' || echo 'NO')"
	@echo "Git available: $(which git >/dev/null 2>&1 && echo 'YES' || echo 'NO')"
	@echo "X11 dev libs: $(pkg-config --exists x11 xext && echo 'YES' || echo 'NO')"
	@echo "Source files:"
	@ls -la src/ 2>/dev/null || echo "src/ directory not found"
	@echo "========================"
