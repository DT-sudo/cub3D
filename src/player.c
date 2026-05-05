/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:50:30 by olcherno          #+#    #+#             */
/*   Updated: 2026/05/04 12:15:11 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_app *app)
{
	app->player.eye_x = app->map.player_x + 0.5;
	app->player.eye_y = app->map.player_y + 0.5;
	if (app->map.player_dir == 'N')
	{
		app->player.face_x = 0;
		app->player.face_y = -1;
	}
	else if (app->map.player_dir == 'S')
	{
		app->player.face_x = 0;
		app->player.face_y = 1;
	}
	else if (app->map.player_dir == 'E')
	{
		app->player.face_x = 1;
		app->player.face_y = 0;
	}
	else
	{
		app->player.face_x = -1;
		app->player.face_y = 0;
	}
	app->player.fov_x = -app->player.face_y * FOV;
	app->player.fov_y = app->player.face_x * FOV;
}

static void	rotate_view(t_app *app, double angle)
{
	double	old_face_x;
	double	old_fov_x;

	old_face_x = app->player.face_x;
	app->player.face_x = old_face_x * cos(angle)
		- app->player.face_y * sin(angle);
	app->player.face_y = old_face_x * sin(angle)
		+ app->player.face_y * cos(angle);
	old_fov_x = app->player.fov_x;
	app->player.fov_x = old_fov_x * cos(angle)
		- app->player.fov_y * sin(angle);
	app->player.fov_y = old_fov_x * sin(angle)
		+ app->player.fov_y * cos(angle);
}

static double	frame_delta(t_app *app)
{
	struct timeval	tv;
	double			current;
	double			dt;

	gettimeofday(&tv, NULL);
	current = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	if (app->last_time == 0)
		app->last_time = current;
	dt = current - app->last_time;
	app->last_time = current;
	return (dt);
}

void	update_player(t_app *app)
{
	double	dt;
	double	move_step;
	double	rot_step;

	dt = frame_delta(app);
	move_step = MOVE_SPEED * dt;
	rot_step = ROT_SPEED * dt;
	if (app->keys.move_forward)
		try_move(app, app->player.face_x * move_step,
			app->player.face_y * move_step);
	if (app->keys.move_back)
		try_move(app, -app->player.face_x * move_step,
			-app->player.face_y * move_step);
	if (app->keys.move_left)
		try_move(app, app->player.face_y * move_step,
			-app->player.face_x * move_step);
	if (app->keys.move_right)
		try_move(app, -app->player.face_y * move_step,
			app->player.face_x * move_step);
	if (app->keys.turn_left)
		rotate_view(app, -rot_step);
	if (app->keys.turn_right)
		rotate_view(app, rot_step);
}
