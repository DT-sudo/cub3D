/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:47:31 by dtereshc          #+#    #+#             */
/*   Updated: 2026/06/15 17:15:58 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static const int	g_dy[4] = {-1, 1, 0, 0};
static const int	g_dx[4] = {0, 0, -1, 1};

static int	chk_neighbor(t_app *app, t_flood *flood, int ny, int nx)
{
	char	cell;

	if (ny < 0 || ny >= app->map.height || nx < 0
		|| nx >= (int)ft_strlen(app->map.grid[ny]))
		return (1);
	cell = app->map.grid[ny][nx];
	if (cell == ' ')
		return (1);
	if (cell == '0' && !flood->visited[ny][nx])
	{
		flood->visited[ny][nx] = 1;
		flood->stack[flood->top++] = ny * app->map.width + nx;
	}
	return (0);
}

static int	alloc_flood(t_app *app, t_flood *flood)
{
	int	y;

	flood->visited = (char **)ft_calloc((size_t)app->map.height,
			sizeof(char *));
	if (!flood->visited)
		return (1);
	y = 0;
	while (y < app->map.height)
	{
		flood->visited[y] = ft_calloc((size_t)app->map.width, sizeof(char));
		if (!flood->visited[y])
			return (1);
		y++;
	}
	flood->stack = malloc(sizeof(int) * app->map.width * app->map.height);
	return (flood->stack == NULL);
}

static void	free_flood(t_app *app, t_flood *flood)
{
	int	y;

	if (flood->visited)
	{
		y = 0;
		while (y < app->map.height)
			free(flood->visited[y++]);
		free(flood->visited);
	}
	free(flood->stack);
}

static int	flood_fill(t_app *app, t_flood *flood)
{
	int	y;
	int	x;
	int	dir;

	while (flood->top > 0)
	{
		y = flood->stack[--flood->top] / app->map.width;
		x = flood->stack[flood->top] % app->map.width;
		dir = 0;
		while (dir < 4)
		{
			if (chk_neighbor(app, flood, y + g_dy[dir], x + g_dx[dir]))
				return (1);
			dir++;
		}
	}
	return (0);
}

int	chk_map_closed(t_app *app)
{
	t_flood	flood;
	int		result;

	ft_bzero(&flood, sizeof(flood));
	if (alloc_flood(app, &flood))
	{
		free_flood(app, &flood);
		return (1);
	}
	flood.stack[flood.top++] = app->map.player_y * app->map.width
		+ app->map.player_x;
	flood.visited[app->map.player_y][app->map.player_x] = 1;
	result = flood_fill(app, &flood);
	free_flood(app, &flood);
	return (result);
}
