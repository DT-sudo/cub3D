/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 09:15:05 by dtereshc          #+#    #+#             */
/*   Updated: 2026/06/15 17:14:40 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		close_app(app);
	else if (keycode == KEY_W)
		app->keys.move_forward = 1;
	else if (keycode == KEY_S)
		app->keys.move_back = 1;
	else if (keycode == KEY_A)
		app->keys.move_left = 1;
	else if (keycode == KEY_D)
		app->keys.move_right = 1;
	else if (keycode == KEY_LEFT)
		app->keys.turn_left = 1;
	else if (keycode == KEY_RIGHT)
		app->keys.turn_right = 1;
	return (0);
}

int	key_release(int keycode, t_app *app)
{
	if (keycode == KEY_W)
		app->keys.move_forward = 0;
	else if (keycode == KEY_S)
		app->keys.move_back = 0;
	else if (keycode == KEY_A)
		app->keys.move_left = 0;
	else if (keycode == KEY_D)
		app->keys.move_right = 0;
	else if (keycode == KEY_LEFT)
		app->keys.turn_left = 0;
	else if (keycode == KEY_RIGHT)
		app->keys.turn_right = 0;
	return (0);
}

void	setup_hooks(t_app *app)
{
	mlx_hook(app->win, 17, 0, (int (*)())close_app, app);
	mlx_hook(app->win, 2, 1L << 0, (int (*)())key_press, app);
	mlx_hook(app->win, 3, 1L << 1, (int (*)())key_release, app);
	mlx_loop_hook(app->mlx, (int (*)())render, app);
}
