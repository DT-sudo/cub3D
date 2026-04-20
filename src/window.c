/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:04 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_app(t_app *app)
{
	free_textures(app);
	if (app->img && app->mlx)
		mlx_destroy_image(app->mlx, app->img);
	if (app->win && app->mlx)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
		mlx_destroy_display(app->mlx);
	free(app->mlx);
	free(app->config.no_texture);
	free(app->config.so_texture);
	free(app->config.we_texture);
	free(app->config.ea_texture);
	if (app->map.grid)
		free_strtab(app->map.grid);
	ft_bzero(app, sizeof(*app));
}

int	close_app(t_app *app)
{
	free_app(app);
	exit(0);
	return (0);
}

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		ft_putstr_fd("Error\nmlx_init failed\n", 2);
		exit(1);
	}
	app->win = mlx_new_window(app->mlx, app->width, app->height, WIN_TITLE);
	if (!app->win)
	{
		free_app(app);
		ft_putstr_fd("Error\nmlx_new_window failed\n", 2);
		exit(1);
	}
	initialize_image(app);
}
