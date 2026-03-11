/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:45 by olcherno          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:24 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs/libft/libft.h"
# include "libs/minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>

# define WIN_W		1280
# define WIN_H		720
# define WIN_TITLE	"cub3D"

# define FOV		0.66

# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

# define MOVE_SPEED	3.0
# define ROT_SPEED	2.2
# define WALL_MARGIN	0.2

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_config
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	int			has_no;
	int			has_so;
	int			has_we;
	int			has_ea;
	int			has_floor;
	int			has_ceiling;
	t_texture	tex_no;
	t_texture	tex_so;
	t_texture	tex_we;
	t_texture	tex_ea;
}	t_config;

typedef struct s_player
{
	double	eye_x;
	double	eye_y;
	double	face_x;
	double	face_y;
	double	fov_x;
	double	fov_y;
}	t_player;

typedef struct s_ray
{
	double		dir_vec_x;
	double		dir_vec_y;
	double		step_unit_x;
	double		step_unit_y;
	double		edge_dist_x;
	double		edge_dist_y;
	double		wall_dstns;
	int			cell_x;
	int			cell_y;
	int			grid_step_x;
	int			grid_step_y;
	int			hit_side;
	int			wall_height;
	int			draw_top;
	int			draw_bottom;
	int			tex_col;
	t_texture	*txtr;
}	t_ray;

typedef struct s_flood
{
	int		*stack;
	int		top;
	char	**visited;
}	t_flood;

typedef struct s_keys
{
	int	move_forward;
	int	move_back;
	int	move_left;
	int	move_right;
	int	turn_left;
	int	turn_right;
}	t_keys;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_map		map;
	t_config	config;
	t_player	player;
	t_keys		keys;
	double		last_time;

	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_app;

/* pars.c */
int		parse_cub(const char *path, t_app *app);
void	free_app(t_app *app);
void	free_strtab(char **tab);

/* pars_lines.c */
char	*dup_line(const char *line);
int		is_blank_line(const char *line);
int		is_map_line(const char *line);
void	append_grid_line(t_app *app, char *line);

/* pars_header.c */
int		parse_header_line(t_app *app, char *line);

/* pars_map.c */
int		map_valid(t_app *app);

/* pars_utils.c */
int		chk_map_closed(t_app *app);

/* textures.c */
int		load_textures(t_app *app);
void	free_textures(t_app *app);

/* player.c */
void	init_player(t_app *app);
void	update_player(t_app *app);

/* player_move.c */
int		is_wall(t_app *app, double x, double y);
void	try_move(t_app *app, double move_dx, double move_dy);

/* raycast.c */
int		cell_is_wall(t_app *app, int x, int y);
void	render_frame(t_app *app);

/* raycast_draw.c */
void	draw_column(t_app *app, int x, t_ray *ray);

/* window.c */
void	init_app(t_app *app);
int		close_app(t_app *app);

/* hooks.c */
int		key_press(int keycode, t_app *app);
int		key_release(int keycode, t_app *app);
void	setup_hooks(t_app *app);

/* window1.c */
void	initialize_image(t_app *app);
void	put_pixel(t_app *app, int x, int y, int color);
int		render(t_app *app);

#endif
