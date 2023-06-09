# ==============================================================================
# PATH
# ==============================================================================

MANDATORY		:= ./mandatory

LIBFT_PATH		:= ./libs/libft
LIBFT_FULL_PATH = $(LIBFT_PATH)/libft.a

MINILIBX_DIR		= ./libs/minilibx
MINILIBX			= ./libs/minilibx/libmlx.a
MINILIBX_FLAGS		= -L. -lXext -L. -lX11


GAME_INIT				:= $(MANDATORY)/game_init
ERROR_HANDLER			:= $(MANDATORY)/error_handler
GAME_EVENTS				:= $(MANDATORY)/game_events
GAME_EXIT				:= $(MANDATORY)/game_exit
MAP_VALIDATION			:= $(MANDATORY)/map_validation
PLAYER					:= $(MANDATORY)/player
RAYCASTING				:= $(MANDATORY)/raycasting
WALLS					:= $(MANDATORY)/walls
GAME					:= $(MANDATORY)/game
DEBUG					:= $(MANDATORY)/debug

# ==============================================================================
# VARIABLES
# ==============================================================================
NAME			:=	cub3D
CC				:=	cc
CFLAGS			:=	-g3 -Wall -Werror -Wextra
MAKE			:=	make

INCLUDES_USR	:= -I./usr/include
INCLUDES		:= -I$(LIBFT_PATH)/includes -I$(MANDATORY)/includes

LIBRARY_MLX_PATH = -L/usr/lib -lmlx -lXext -lX11 -lm -lz

SRCS	:=		$(MANDATORY)/cub3D.c \
				$(GAME)/game.c $(GAME)/minimap.c \
				$(GAME_INIT)/game_init.c $(GAME_INIT)/game_init_utils.c \
				$(GAME_INIT)/images_init.c \
				$(ERROR_HANDLER)/error_handler.c \
				$(GAME_EVENTS)/game_events.c \
				$(GAME_EXIT)/game_exit.c $(GAME_EXIT)/game_exit_utils.c \
				$(MAP_VALIDATION)/map_validation.c $(MAP_VALIDATION)/file_helpers.c \
				$(MAP_VALIDATION)/map_validation_utils.c $(MAP_VALIDATION)/map_validation_utils_II.c \
				$(MAP_VALIDATION)/map_properties_utils.c $(MAP_VALIDATION)/map_content_utils.c \
				$(MAP_VALIDATION)/map_content_utils_II.c $(MAP_VALIDATION)/map_properties_utils_II.c \
				$(MAP_VALIDATION)/map_loaders.c \
				$(PLAYER)/map_utils.c $(PLAYER)/rectangle.c $(PLAYER)/player.c \
				$(PLAYER)/line.c $(PLAYER)/render_player.c $(PLAYER)/player_utils.c\
				$(PLAYER)/graphics.c $(PLAYER)/images_utils.c \
				$(RAYCASTING)/calculate_rays.c $(RAYCASTING)/ray_facing.c \
				$(RAYCASTING)/calculate_vertical_coordinates.c  $(RAYCASTING)/calculate_horizontal_coordinates.c \
				$(RAYCASTING)/calculate_steps.c $(RAYCASTING)/ray_utils.c $(RAYCASTING)/render_rays.c \
				$(RAYCASTING)/vertical_utils.c $(RAYCASTING)/horizontal_utils.c  $(RAYCASTING)/cast_rays.c\
				$(WALLS)/walls.c $(WALLS)/wall_utils.c $(WALLS)/calc_dist_wall.c \
				$(DEBUG)/debug.c


OBJS		:=	$(SRCS:.c=.o)


# ==============================================================================
# COLORS
# ==============================================================================

GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
WHT			:=	\033[1;37m
EOC			:=	\033[1;0m

# ==============================================================================
# RECIPES
# ==============================================================================

define COMPILE_DONE
 ____ ____ ____ ____ ____
||C |||U |||B |||3 |||D ||
||__|||__|||__|||__|||__||
|/__\|/__\|/__\|/__\|/__\|
endef
export COMPILE_DONE

all:		$(NAME)


%.o:		%.c
			@$(CC) $(CFLAGS) $(INCLUDES_USR) $(INCLUDES) -c $< -o $@


$(NAME):		$(LIBFT_FULL_PATH) $(MINILIBX) $(OBJS)
				@echo "$(WHT)Compiling Cub3D...$(EOC)"
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FULL_PATH) $(MINILIBX) $(MINILIBX_FLAGS) -o $(NAME)
				@echo "$(GREEN)Cub3D build completed.$(EOC)"
				@tput setaf 5
				@echo "$$COMPILE_DONE"

$(LIBFT_FULL_PATH):
			@$(MAKE) -C $(LIBFT_PATH)


$(MINILIBX):		
			$(MAKE) -C $(MINILIBX_DIR)

clean:
			@echo "$(WHT)Removing .o files...$(EOC)"
			$(MAKE) clean -C $(LIBFT_PATH)
			$(MAKE) clean -C $(MINILIBX_DIR)
			@echo "$(GREEN)Clean done.$(EOC)"

fclean:		clean
			@echo "$(WHT)Removing object- and binary -files...$(EOC)"
			$(MAKE) fclean -C $(LIBFT_PATH)
			@echo "$(GREEN)Fclean done.$(EOC)"

re:			fclean all

valgrind:
			@valgrind -s --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --trace-children=yes --log-fd=9 ./$(NAME) $(MAP) 9>memcheck.log

.PHONY:		all clean fclean re
