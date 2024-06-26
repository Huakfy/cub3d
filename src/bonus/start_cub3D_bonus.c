/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3D_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:06:48 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 17:31:28 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	constant_loop2(t_mlx *mlx)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(mlx->ptr, mlx->win, &x, &y);
	if (x < WIDTH / 2 - 1)
		movement3(RLEFT, mlx->ray);
	else if (x > WIDTH / 2)
		movement3(RRIGHT, mlx->ray);
	mlx_mouse_move(mlx->ptr, mlx->win, (WIDTH / 2) - 1, (HEIGHT / 2) - 1);
}

static int	constant_loop(t_mlx *mlx)
{
	mlx->frames++;
	if (mlx->frames % REFRESH_RATE == 0)
		render_screen(mlx);
	if (mlx->frames % REFRESH_RATE_MOVE == 0)
	{
		if (mlx->front)
			movement(FRONT, mlx->data, mlx->ray);
		if (mlx->back)
			movement(BACK, mlx->data, mlx->ray);
		if (mlx->left)
			movement2(LEFT, mlx->data, mlx->ray);
		if (mlx->right)
			movement2(RIGHT, mlx->data, mlx->ray);
		if (mlx->rleft)
			movement3(RLEFT, mlx->ray);
		if (mlx->rright)
			movement3(RRIGHT, mlx->ray);
		constant_loop2(mlx);
	}
	return (0);
}

static void	init_mlx_values(t_rayc *ray, t_map *data)
{
	ray->posx = pos_to_x(data->start_pos, data->nb_col) + 0.5;
	ray->posy = pos_to_y(data->start_pos, data->nb_col) + 0.5;
	if (data->start_dir == 'N')
	{
		ray->diry = -1;
		ray->planex = 0.66;
	}
	else if (data->start_dir == 'S')
	{
		ray->diry = 1;
		ray->planex = -0.66;
	}
	else if (data->start_dir == 'W')
	{
		ray->dirx = -1;
		ray->planey = -0.66;
	}
	else if (data->start_dir == 'E')
	{
		ray->dirx = 1;
		ray->planey = 0.66;
	}
}

int	start_cub3d(t_mlx *mlx, t_map *data)
{
	init_mlx_values(mlx->ray, data);
	mlx_loop_hook(mlx->ptr, &constant_loop, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, mlx);
	mlx_hook(mlx->win, ClientMessage, LeaveWindowMask, &cross_press, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
