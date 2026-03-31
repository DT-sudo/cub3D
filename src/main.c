/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:17 by olcherno          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:21 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	chk_args(int ac, char **av)
{
	size_t	len;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 5 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nmap file must have .cub extension\n", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;

	if (chk_args(ac, av))
		return (1);
	ft_bzero(&app, sizeof(app));
	app.width = WIN_W;
	app.height = WIN_H;
	if (parse_cub(av[1], &app))
	{
		free_app(&app);
		return (1);
	}
	init_app(&app);
	if (load_textures(&app))
	{
		ft_putstr_fd("Error\nfailed to load a wall texture\n", 2);
		free_app(&app);
		return (1);
	}
	init_player(&app);
	setup_hooks(&app);
	mlx_loop(app.mlx);
	return (0);
}
