/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:06:48 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/29 12:38:34 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	constant_loop(t_mlx *mlx)
{
	mlx->frames++;
	if (mlx->frames % 1000 == 0)
		render_screen(mlx);
	return (0);
}

static void	init_mlx_values(t_map *data)
{
	data->posX = pos_to_x(data->start_pos, data->nb_col) + 0.5;
	data->posY = pos_to_y(data->start_pos, data->nb_col) + 0.5;
	if (data->start_dir == 'N')
	{
		data->dirY = -1;
		data->planeX = 0.66;
	}
	else if (data->start_dir == 'S')
	{
		data->dirY = 1;
		data->planeX = -0.66;

	}
	else if (data->start_dir == 'W')
	{
		data->dirX = -1;
		data->planeY = -0.66;
	}
	else if (data->start_dir == 'E')
	{
		data->dirX = 1;
		data->planeY = 0.66;

	}
}

int	start_cub3D(t_mlx *mlx,t_map *data)
{
	init_mlx_values(data);
	mlx_loop_hook(mlx->ptr, &constant_loop, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, ClientMessage, LeaveWindowMask, &cross_press, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}