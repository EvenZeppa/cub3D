# 🏳️‍🌈 Définition des couleurs
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
BOLD    = \033[1m

# 🏳️‍🌈 Définition de la variable de bascule
IS_LIBFT ?= true

# 🛠 Compilateur et flags
CC = gcc
CFLAGS =
LDFLAGS =

# 🏆 Nom du projet
PROJECT_NAME = cub3D

# 🖥️ Détection de l'OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	CFLAGS   += -I/usr/include -Iminilibx-linux
	LDFLAGS  += -L/usr/lib -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
	MLX_DIR   = minilibx-linux
else ifeq ($(UNAME_S), Darwin)
	CFLAGS   += -I/opt/homebrew/include -Iminilibx-mac-2
	LDFLAGS  += -L/opt/homebrew/lib -Lminilibx-mac-2 -lmlx -framework OpenGL -framework AppKit
	MLX_DIR   = minilibx-mac-2
endif

# 📂 Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# 📌 Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# 📚 Inclusion des headers
INCLUDES = -I$(INCLUDE_DIR)

ifeq ($(IS_LIBFT), true)
	LIBFT_DIR = mylib
	LIBFT = $(LIBFT_DIR)/lib/libft.a
	LIBFT_REPO = https://github.com/Corgidev42/mylib.git
	LIBFT_INCLUDE = -I$(LIBFT_DIR)/include
	INCLUDES += $(LIBFT_INCLUDE)
endif

# 🎯 Règle principale
all: $(MLX_DIR) $(PROJECT_NAME)

# 🏗️ Compilation de l’exécutable
$(PROJECT_NAME): $(OBJ_FILES) $(LIBFT)
	@echo "${MAGENTA}🚀 Compilation de $(PROJECT_NAME)...${RESET}"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) $(LDFLAGS) $(LIBFT) -o $@
	@echo "${GREEN}✅ Compilation terminée !${RESET}"

# 🛠️ Compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
	@echo "${CYAN}🔨 Compilé : $< -> $@${RESET}"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# 📦 Compilation de libft
ifeq ($(IS_LIBFT), true)
$(LIBFT_DIR):
	@git clone $(LIBFT_REPO) $(LIBFT_DIR)

$(LIBFT): | $(LIBFT_DIR)
	@if [ ! -f $(LIBFT) ]; then \
		echo "${YELLOW}📥 Compilation de libft...${RESET}"; \
		make -C $(LIBFT_DIR); \
	else \
		echo "${GREEN}✅ libft déjà compilée.${RESET}"; \
	fi
endif

# 📦 Compilation de MiniLibX
$(MLX_DIR):
	@echo "${YELLOW}📦 Compilation de MiniLibX dans $(MLX_DIR)...${RESET}"
	@$(MAKE) -C $(MLX_DIR)

# 🧹 Nettoyage
clean:
	@rm -rf $(OBJ_DIR)
ifeq ($(IS_LIBFT), true)
	@if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) clean; fi
endif
	@if [ -d $(MLX_DIR) ]; then make -C $(MLX_DIR) clean; fi
	@echo "${RED}🗑️  Fichiers objets nettoyés.${RESET}"

fclean: clean
	@rm -f $(PROJECT_NAME)
ifeq ($(IS_LIBFT), true)
	@rm -rf $(LIBFT_DIR)
endif
	@echo "${RED}🗑️  Nettoyage complet effectué.${RESET}"

re: fclean all

run: all
	@echo "${BLUE}▶️  Exécution de $(PROJECT_NAME)...${RESET}"
	@./$(PROJECT_NAME) $(ARGS)

val: all
	@echo "${BLUE}🧠 Analyse mémoire avec Valgrind...${RESET}"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROJECT_NAME) $(ARGS)

.PHONY: all clean fclean re run val $(MLX_DIR)
