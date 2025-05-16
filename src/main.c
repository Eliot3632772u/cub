/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:43:17 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/16 18:44:30 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(t_info *info)
{
	init_mlx(info);
	init_vars(info);
	init_map_data(info);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
	{
		printf("Error\nWrong Usage\n");
		return (1);
	}
	info.file_name = av[1];
	init_info(&info);
	mlx_hook(info.mlx.win, 3, 1L << 1, release, &info);
	mlx_hook(info.mlx.win, 2, 1L << 0, press, &info);
	mlx_hook(info.mlx.win, 6, 1L << 6, mouse_move, &info);
	mlx_hook(info.mlx.win, 17, 0, exit_prog, &info);
	mlx_loop_hook(info.mlx.con, raycasting, &info);
	mlx_loop(info.mlx.con);
}
