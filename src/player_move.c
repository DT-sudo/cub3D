/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:40:36 by olcherno          #+#    #+#             */
/*   Updated: 2026/05/06 14:58:23 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_app *app, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= app->map.height)
		return (1);
	if (mx < 0 || mx >= (int)ft_strlen(app->map.grid[my]))
		return (1);
	return (app->map.grid[my][mx] != '0');
}

void	try_move(t_app *app, double move_dx, double move_dy)
{
	double	new_x;
	double	new_y;
	double	margin_x;
	double	margin_y;

	new_x = app->player.eye_x + move_dx;
	new_y = app->player.eye_y + move_dy;
	margin_x = WALL_MARGIN;
	if (move_dx < 0)
		margin_x = -WALL_MARGIN;
	margin_y = WALL_MARGIN;
	if (move_dy < 0)
		margin_y = -WALL_MARGIN;
	if (!is_wall(app, new_x + margin_x, app->player.eye_y))
		app->player.eye_x = new_x;
	if (!is_wall(app, app->player.eye_x, new_y + margin_y))
		app->player.eye_y = new_y;
}
