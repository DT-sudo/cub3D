/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:30:32 by dtereshc          #+#    #+#             */
/*   Updated: 2026/04/03 16:05:37 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	chk_cell(t_app *app, int x, int y, int *players)
{
	char	cell;

	cell = app->map.grid[y][x];
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		app->map.player_x = x;
		app->map.player_y = y;
		app->map.player_dir = cell;
		(*players)++;
		app->map.grid[y][x] = '0';
		return (0);
	}
	if (cell != '0' && cell != '1' && cell != ' ')
		return (1);
	return (0);
}

int	map_valid(t_app *app)
{
	int	y;
	int	x;
	int	players;

	players = 0;
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(app->map.grid[y]))
		{
			if (chk_cell(app, x, y, &players))
				return (1);
			x++;
		}
		y++;
	}
	if (players != 1)
		return (1);
	return (chk_map_closed(app));
}
