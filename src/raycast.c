/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:02:59 by olcherno          #+#    #+#             */
/*   Updated: 2026/05/20 20:10:25 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cell_is_wall(t_app *app, int x, int y)
{
	if (y < 0 || y >= app->map.height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(app->map.grid[y]))
		return (1);
	return (app->map.grid[y][x] == '1');
}

static double	init_axis(double pos, double dir, int *step, double *side)
{
	double	delta;

	delta = fabs(1.0 / dir);
	if (dir < 0)
	{
		*step = -1;
		*side = (pos - (int)pos) * delta;
	}
	else
	{
		*step = 1;
		*side = ((int)pos + 1.0 - pos) * delta;
	}
	return (delta);
}

static void	init_dda(t_app *app, t_ray *ray)
{
	ray->cell_x = (int)app->player.eye_x;
	ray->cell_y = (int)app->player.eye_y;
	ray->step_unit_x = init_axis(app->player.eye_x, ray->dir_vec_x,
			&ray->grid_step_x, &ray->edge_dist_x);
	ray->step_unit_y = init_axis(app->player.eye_y, ray->dir_vec_y,
			&ray->grid_step_y, &ray->edge_dist_y);
}

static void	perform_dda(t_app *app, t_ray *ray)
{
	while (!cell_is_wall(app, ray->cell_x, ray->cell_y))
	{
		if (ray->edge_dist_x < ray->edge_dist_y)
		{
			ray->edge_dist_x += ray->step_unit_x;
			ray->cell_x += ray->grid_step_x;
			ray->hit_side = 0;
		}
		else
		{
			ray->edge_dist_y += ray->step_unit_y;
			ray->cell_y += ray->grid_step_y;
			ray->hit_side = 1;
		}
	}
	if (ray->hit_side == 0)
		ray->wall_dstns = (ray->cell_x - app->player.eye_x
				+ (1 - ray->grid_step_x) / 2.0) / ray->dir_vec_x;
	else
		ray->wall_dstns = (ray->cell_y - app->player.eye_y
				+ (1 - ray->grid_step_y) / 2.0) / ray->dir_vec_y;
}

void	render_frame(t_app *app)
{
	int		x;
	t_ray	ray;
	double	camera_x;

	x = 0;
	while (x < app->width)
	{
		camera_x = 2.0 * x / (double)app->width - 1.0;
		ray.dir_vec_x = app->player.face_x + app->player.fov_x * camera_x;
		ray.dir_vec_y = app->player.face_y + app->player.fov_y * camera_x;
		init_dda(app, &ray);
		perform_dda(app, &ray);
		draw_column(app, x, &ray);
		x++;
	}
}
