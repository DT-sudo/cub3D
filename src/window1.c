/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:02:00 by olcherno          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:50 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_image(t_app *app)
{
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
	{
		ft_putstr_fd("Error\nmlx_new_image failed\n", 2);
		close_app(app);
	}
	app->addr = mlx_get_data_addr(app->img, &app->bpp, &app->line_len,
			&app->endian);
	if (!app->addr)
	{
		ft_putstr_fd("Error\nmlx_get_data_addr failed\n", 2);
		close_app(app);
	}
}

void	put_pixel(t_app *app, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return ;
	offset = y * app->line_len + x * (app->bpp / 8);
	*(int *)(app->addr + offset) = color;
}

int	render(t_app *app)
{
	update_player(app);
	render_frame(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (0);
}
