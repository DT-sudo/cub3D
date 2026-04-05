/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:05:55 by dtereshc          #+#    #+#             */
/*   Updated: 2026/03/19 14:22:09 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_color(int *dst, const char *line)
{
	int	index;
	int	red;
	int	green;
	int	blue;

	index = 1;
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	red = ft_atoi(line + index);
	while (line[index] && line[index] != ',')
		index++;
	if (line[index] != ',')
		return (1);
	green = ft_atoi(line + ++index);
	while (line[index] && line[index] != ',')
		index++;
	if (line[index] != ',')
		return (1);
	blue = ft_atoi(line + ++index);
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
		return (1);
	*dst = (red << 16) | (green << 8) | blue;
	return (0);
}

static int	set_texture(char **dst, int *has_flag, const char *line,
		int prefix_len)
{
	int	start;

	start = prefix_len;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	free(*dst);
	*dst = dup_line(line + start);
	if (*dst && (*dst)[0] == '\0')
	{
		free(*dst);
		*dst = NULL;
	}
	*has_flag = (*dst != NULL);
	return (0);
}

static int	parse_texture_line(t_app *app, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (set_texture(&app->config.no_texture,
				&app->config.has_no, line, 2));
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (set_texture(&app->config.so_texture,
				&app->config.has_so, line, 2));
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (set_texture(&app->config.we_texture,
				&app->config.has_we, line, 2));
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (set_texture(&app->config.ea_texture,
				&app->config.has_ea, line, 2));
	return (-1);
}

static int	parse_color_line(t_app *app, const char *line)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		app->config.has_floor = (set_color(&app->config.floor_color,
					line) == 0);
		return (!app->config.has_floor);
	}
	if (line[0] == 'C' && line[1] == ' ')
	{
		app->config.has_ceiling = (set_color(&app->config.ceiling_color,
					line) == 0);
		return (!app->config.has_ceiling);
	}
	return (-1);
}

int	parse_header_line(t_app *app, char *line)
{
	int	ret;

	ret = parse_texture_line(app, line);
	if (ret >= 0)
		return (ret);
	ret = parse_color_line(app, line);
	if (ret >= 0)
		return (ret);
	return (1);
}
