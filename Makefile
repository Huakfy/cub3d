NAME	=	cub3D

CC		=	cc
FLAG	=	-Wall -Wextra -Werror -g3

DIRLIB	=	./libft/
FT_FLAGS =	-Llibft -lft

PATH_MLX = ./minilibx-linux
MLX_FLAGS = -Lminilibx-linux -lmlx -lmlx_Linux -lXext -lX11 -lm

LDFLAGS = $(FT_FLAGS) $(MLX_FLAGS)

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./include -I ./libft/src -I $(PATH_MLX)
HEADER	=	include/cub3D.h

# Source
FILES	=	main parsing_textures data_utils parsing_map convert_pos_x_y parsing_mlx mlx_utils render start_cub3D

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

# Add the path to the builtin folder to vpath
vpath %.c $(SRC_DIR) $(SRC_DIR)/parsing $(SRC_DIR)/utils $(SRC_DIR)/mlx

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(DIRLIB)
	@make -C $(PATH_MLX)
	$(CC) $(FLAG) $(OBJS) $(LDFLAGS) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)$(NAME) Compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : %.c $(HEADER) Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean :
	@make clean -sC $(DIRLIB)
	@make clean -sC $(PATH_MLX)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo "$(MAGENTA)$(NAME) objects cleaned !$(DEF_COLOR)"

fclean : clean
	@make clean -sC $(DIRLIB)
	@make clean -sC $(PATH_MLX)
	@rm -rf $(NAME)
	@echo "$(YELLOW)$(NAME) cleaned !$(DEF_COLOR)"

re : fclean all
	@echo "$(GREEN)Cleaned and rebuilt !$(DEF_COLOR)"

.PHONY : all clean fclean re

# Color
DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
