# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wno-cast-function-type

NAME = cub3D
NAME_BONUS = cub3D_bonus

# Paths
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libs/libft
MLXDIR = libs/minilibx
IFLAGS = -I. -I$(LIBFTDIR) -I$(MLXDIR)

# Link flags
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
MLX_LIB = $(MLXDIR)/libmlx.a
MLX_FLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
else
MLX_LIB = $(MLXDIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLXDIR) -lmlx_Linux -lXext -lX11 -lm -lz
endif
LIBS = -L$(LIBFTDIR) -lft

# Sources
SRC = main.c window.c window1.c hooks.c \
      pars.c pars_lines.c pars_header.c pars_map.c pars_utils.c \
      textures.c player.c player_move.c raycast.c raycast_draw.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJS_BONUS = $(OBJS)

# Main rule
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a $(MLX_LIB)
	$(CC) $(CFLAGS) -no-pie $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFTDIR)/libft.a $(MLX_LIB)
	$(CC) $(CFLAGS) -no-pie $(OBJS_BONUS) $(LIBS) $(MLX_FLAGS) -o $(NAME_BONUS)

# Compile .c → .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Create obj/
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build libraries
$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(LIBFTDIR)

$(MLX_LIB):
	$(MAKE) -C $(MLXDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(MLXDIR) clean

re: fclean all

# Standard rules
.PHONY: all bonus clean fclean re