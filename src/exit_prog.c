/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:53:05 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/13 10:04:06 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int    exit_prog(void *inf)
{
    t_info  *info;

    info = inf;
    (void)info;
    printf("exit_prog func called\n");
    exit(0);
}