/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:36:54 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/16 18:16:44 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_allocs(t_info *info, char *alloc)
{
	int	i;

	if (alloc)
		free(alloc);
	if (info->north)
		free(info->north);
	if (info->south)
		free(info->south);
	if (info->east)
		free(info->east);
	if (info->west)
		free(info->west);
	if (info->doors)
		free(info->doors);
	if (info->map)
	{
		i = -1;
		while (++i < info->map_h)
			free(info->map[i]);
		free(info->map);
	}
}

void	close_fd(int fd)
{
	if (fd > 0)
	{
		close(fd);
	}
}

void	destroy_mlx(t_info *info)
{
	mlx_destroy_image(info->mlx.con, info->mlx.img);
	mlx_destroy_window(info->mlx.con, info->mlx.win);
	mlx_destroy_display(info->mlx.con);
	free(info->mlx.con);
}

void	free_and_exit(t_info *info, char *alloc, char *error_msg)
{
	destroy_mlx(info);
	close_fd(info->fd);
	free_allocs(info, alloc);
	if (error_msg)
	{
		printf("Error\n%s\n", error_msg);
		exit(1);
	}
	exit(0);
}
