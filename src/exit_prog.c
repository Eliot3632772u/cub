/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:53:05 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:52:46 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_prog(void *inf)
{
	t_info	*info;

	info = inf;
	free_textures(info);
	free_and_exit(info, NULL, NULL);
	printf("exit_prog func called\n");
	exit(0);
	return (0);
}
