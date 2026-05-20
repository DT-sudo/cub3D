/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 13:25:01 by olcherno          #+#    #+#             */
/*   Updated: 2026/05/25 17:48:49 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_texture	*select_texture(t_app *app, t_ray *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->grid_step_x > 0)
			return (&app->config.tex_we);
		return (&app->config.tex_ea);
	}
	if (ray->grid_step_y > 0)
		return (&app->config.tex_no);
	return (&app->config.tex_so);
}

static int	comput_tex_col(t_app *app, t_ray *ray, t_texture *txtr)
{
	double	wall_x;
	int		tex_col;

	if (ray->hit_side == 0)
		wall_x = app->player.eye_y + ray->wall_dstns * ray->dir_vec_y;
	else
		wall_x = app->player.eye_x + ray->wall_dstns * ray->dir_vec_x;
	wall_x -= floor(wall_x);
	tex_col = (int)(wall_x * txtr->width);
	if ((ray->hit_side == 0 && ray->dir_vec_x > 0)
		|| (ray->hit_side == 1 && ray->dir_vec_y < 0))
		tex_col = txtr->width - tex_col - 1;
	return (tex_col);
}

static int	textur_pxl(t_texture *txtr, int tex_col, int tex_y)
{
	char	*pxl;

	pxl = txtr->addr + tex_y * txtr->line_len + tex_col * (txtr->bpp / 8);
	return (*(int *)pxl);
}

static void	draw_span(t_app *app, int x, t_ray *ray)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;

	y = 0;
	while (y < ray->draw_top)
		put_pixel(app, x, y++, app->config.ceiling_color);
	step = (double)ray->txtr->height / ray->wall_height;
	tex_pos = (ray->draw_top - app->height / 2.0
			+ ray->wall_height / 2.0) * step;
	while (y <= ray->draw_bottom)
	{
		tex_y = (int)tex_pos & (ray->txtr->height - 1);
		tex_pos += step;
		put_pixel(app, x, y++, textur_pxl(ray->txtr, ray->tex_col, tex_y));
	}
	while (y < app->height)
		put_pixel(app, x, y++, app->config.floor_color);
}

void	draw_column(t_app *app, int x, t_ray *ray)
{
	if (ray->wall_dstns < 0.0001)
		ray->wall_dstns = 0.0001;
	ray->wall_height = (int)(app->height / ray->wall_dstns);
	ray->draw_top = -ray->wall_height / 2 + app->height / 2;
	ray->draw_bottom = ray->wall_height / 2 + app->height / 2;
	if (ray->draw_top < 0)
		ray->draw_top = 0;
	if (ray->draw_bottom >= app->height)
		ray->draw_bottom = app->height - 1;
	ray->txtr = select_texture(app, ray);
	ray->tex_col = comput_tex_col(app, ray, ray->txtr);
	draw_span(app, x, ray);
}
