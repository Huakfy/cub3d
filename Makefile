NAME	=	cub3D

CC		=	cc
#FLAG	=	-Wall -Wextra -Werror -g3 -Lmlx -lmlx -lXext -lX11 -lm
FLAG	=	-Wall -Wextra -Werror -g3 -Lmlx -lXext -lX11 -lm

DIRLIB	=	./libft/
FILELIB	=	libft.a
NAMELFT	=	$(addprefix $(DIRLIB), $(FILELIB))


PATH_MLX = minilibx-linux

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./include -I ./libft -I $(PATH_MLX)
HEADER 	=	include/cub3D.h

# Source
FILES	=	main parsing_textures data_utils parsing_map

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

# Add the path to the builtin folder to vpath
vpath %.c $(SRC_DIR)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(DIRLIB)
	@make -C $(PATH_MLX)
	$(CC) $(FLAG) $(OBJS) $(NAMELFT) $(INCLUDE) -o $(NAME)
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
