/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:00:26 by olcherno          #+#    #+#             */
/*   Updated: 2026/04/21 19:33:52 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	load_one(t_app *app, t_texture *txtr, char *path)
{
	txtr->img = mlx_xpm_file_to_image(app->mlx, path, &txtr->width,
			&txtr->height);
	if (!txtr->img)
		return (1);
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bpp, &txtr->line_len,
			&txtr->endian);
	if (!txtr->addr)
		return (1);
	return (0);
}

int	load_textures(t_app *app)
{
	if (load_one(app, &app->config.tex_no, app->config.no_texture))
		return (1);
	if (load_one(app, &app->config.tex_so, app->config.so_texture))
		return (1);
	if (load_one(app, &app->config.tex_we, app->config.we_texture))
		return (1);
	if (load_one(app, &app->config.tex_ea, app->config.ea_texture))
		return (1);
	return (0);
}

static void	destroy_texture(t_app *app, t_texture *txtr)
{
	if (txtr->img && app->mlx)
		mlx_destroy_image(app->mlx, txtr->img);
	txtr->img = NULL;
}

void	free_textures(t_app *app)
{
	destroy_texture(app, &app->config.tex_no);
	destroy_texture(app, &app->config.tex_so);
	destroy_texture(app, &app->config.tex_we);
	destroy_texture(app, &app->config.tex_ea);
}
