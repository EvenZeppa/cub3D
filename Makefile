# 🏳️‍🌈 Définition des couleurs
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
BOLD    = \033[1m

# 🏆 Nom du projet
PROJECT_NAME = cub3D

# 🏳️‍🌈 Variables de configuration
IS_LIBFT ?= true
IS_MLX ?= true

# 🛠 Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS =

# 🖥️ Détection de l'OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR   = minilibx-linux
	MLX       = $(MLX_DIR)/libmlx_Linux.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
	CFLAGS   += -I/usr/include
else ifeq ($(UNAME_S), Darwin)
	MLX_DIR   = minilibx-mac-2
	MLX       = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -I /opt/X11/include/X11
	CFLAGS   += -I/opt/homebrew/include
	LDFLAGS  += -L/opt/homebrew/lib
endif

ifeq ($(IS_MLX), true)
	CFLAGS += -I$(MLX_DIR)
endif

# 📂 Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# 📌 Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# 📚 Headers
INCLUDES = -I$(INCLUDE_DIR)

# 🔧 libft
ifeq ($(IS_LIBFT), true)
	LIBFT_DIR = mylib
	LIBFT = $(LIBFT_DIR)/lib/libft.a
	LIBFT_REPO = https://github.com/Corgidev42/mylib.git
	LIBFT_INCLUDE = -I$(LIBFT_DIR)/include
	INCLUDES += $(LIBFT_INCLUDE)
endif

# 🎯 Cible principale
all: $(OBJ_DIR)
ifeq ($(IS_LIBFT), true)
all: $(LIBFT)
endif
ifeq ($(IS_MLX), true)
all: $(MLX)
endif
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ_FILES)
	@echo "${MAGENTA}🚀 Compilation de $(PROJECT_NAME)...${RESET}"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) $(LDFLAGS) \
	$(if $(IS_MLX),$(MLX_FLAGS)) \
	$(if $(IS_LIBFT),$(LIBFT)) \
	-o $@
	@echo "${GREEN}✅ Compilation terminée !${RESET}"

# 🛠️ Compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
	@echo "${CYAN}🔨 Compilé : $< -> $@${RESET}"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# 📦 Compilation MLX (si activée)
ifeq ($(IS_MLX), true)
$(MLX):
	@echo "${YELLOW}📦 Compilation de MiniLibX...${RESET}"
	@$(MAKE) -C $(MLX_DIR)
endif

# 📦 Compilation libft (si activée)
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

# 🧹 Nettoyage
clean:
	@rm -rf $(OBJ_DIR)
ifeq ($(IS_MLX), true)
	@$(MAKE) -C $(MLX_DIR) clean
endif
ifeq ($(IS_LIBFT), true)
	@$(MAKE) -C $(LIBFT_DIR) clean
endif
	@echo "${RED}🧼 Objets supprimés.${RESET}"

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

help:
	@echo "${BOLD}${CYAN}--- 📘 Liste des commandes disponibles ---${RESET}"
	@echo "${BOLD}make${RESET}        : Compile le projet ($(PROJECT_NAME))"
	@echo "${BOLD}make clean${RESET}  : Supprime les fichiers objets"
	@echo "${BOLD}make fclean${RESET} : Supprime les objets + exécutable + libft (si activée)"
	@echo "${BOLD}make re${RESET}     : Nettoie puis recompile tout"
	@echo "${BOLD}make run${RESET}    : Compile et exécute le programme"
	@echo "${BOLD}make val${RESET}    : Exécute avec Valgrind (Linux uniquement)"
	@echo "${BOLD}make help${RESET}   : Affiche ce message d’aide"
	@echo ""
	@echo "${BOLD}${CYAN}Options activées :${RESET}"
	@echo "libft : $(IS_LIBFT)"
	@echo "mlx   : $(IS_MLX)"
	@echo "OS détecté : $(UNAME_S)"
	@echo "MiniLibX utilisée : $(if $(IS_MLX),$(MLX_DIR),non utilisée)"

.PHONY: all clean fclean re run val help
