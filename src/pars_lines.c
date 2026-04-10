/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:12:10 by dtereshc          #+#    #+#             */
/*   Updated: 2026/03/15 17:40:47 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*dup_line(const char *line)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	copy[len] = '\0';
	while (len > 0)
	{
		len--;
		copy[len] = line[len];
	}
	return (copy);
}

int	is_blank_line(const char *line)
{
	int	index;

	index = 0;
	while (line[index] == ' ' || line[index] == '\t' || line[index] == '\n'
		|| line[index] == '\r')
		index++;
	return (line[index] == '\0');
}

int	is_map_line(const char *line)
{
	int		index;
	char	c;

	index = 0;
	while (line[index])
	{
		c = line[index];
		if (c != '0' && c != '1' && c != 'N' && c != 'S'
			&& c != 'E' && c != 'W' && c != ' ' && c != '\t'
			&& c != '\n' && c != '\r')
			return (0);
		index++;
	}
	return (1);
}

void	append_grid_line(t_app *app, char *line)
{
	char	**grid;
	int		index;

	grid = malloc(sizeof(char *) * (app->map.height + 2));
	if (!grid)
		return ;
	index = 0;
	while (index < app->map.height)
	{
		grid[index] = app->map.grid[index];
		index++;
	}
	grid[index] = line;
	grid[index + 1] = NULL;
	free(app->map.grid);
	app->map.grid = grid;
	app->map.height++;
	if ((int)ft_strlen(line) > app->map.width)
		app->map.width = ft_strlen(line);
}
