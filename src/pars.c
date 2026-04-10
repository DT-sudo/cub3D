/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:34 by dtereshc          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:20 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_strtab(char **tab)
{
	int	index;

	if (!tab)
		return ;
	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

static int	all_fields_set(t_app *app)
{
	return (app->config.has_no && app->config.has_so
		&& app->config.has_we && app->config.has_ea
		&& app->config.has_floor && app->config.has_ceiling);
}

static int	process_line(t_app *app, char *line, int *map_started)
{
	if (is_blank_line(line))
		return (*map_started);
	if (!*map_started && is_map_line(line))
		*map_started = 1;
	if (*map_started)
	{
		append_grid_line(app, dup_line(line));
		return (0);
	}
	return (parse_header_line(app, line));
}

static int	read_scene_lines(int fd, t_app *app)
{
	char	*line;
	int		map_started;
	int		error;

	map_started = 0;
	error = 0;
	while (!error)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		error = process_line(app, line, &map_started);
		free(line);
	}
	return (error);
}

int	parse_cub(const char *path, t_app *app)
{
	int	fd;
	int	error;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open scene file\n", 2);
		return (1);
	}
	app->map.grid = NULL;
	app->map.width = 0;
	app->map.height = 0;
	app->map.player_x = -1;
	app->map.player_y = -1;
	app->map.player_dir = 0;
	error = read_scene_lines(fd, app);
	close(fd);
	if (error || !app->map.grid || !all_fields_set(app)
		|| map_valid(app))
	{
		ft_putstr_fd("Error\nInvalid or incomplete .cub scene file\n", 2);
		return (1);
	}
	return (0);
}
