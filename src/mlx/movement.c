/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:53:26 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/30 16:15:59 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Norm
static void	movement(int keysym, t_map *data, t_rayc *d)
{
	if (keysym == FRONT)
	{
		if (data->map[coord_to_pos(d->posX + d->dirX * MOVSTEP, d->posY, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX + d->dirX * \
		MOVSTEP, d->posY, data->nb_col)] != ' ')
			d->posX += d->dirX * MOVSTEP;
		if (data->map[coord_to_pos(d->posX, d->posY + d->dirY * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX, d->posY + \
		d->dirY * MOVSTEP, data->nb_col)] != ' ')
			d->posY += d->dirY * MOVSTEP;
	}
	else if (keysym == BACK)
	{
		if (data->map[coord_to_pos(d->posX - d->dirX * MOVSTEP, d->posY, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX - d->dirX * \
		MOVSTEP, d->posY, data->nb_col)] != ' ')
			d->posX -= d->dirX * MOVSTEP;
		if (data->map[coord_to_pos(d->posX, d->posY - d->dirY * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX, d->posY - \
		d->dirY * MOVSTEP, data->nb_col)] != ' ')
			d->posY -= d->dirY * MOVSTEP;
	}
}

//Norm
static void	movement2(int keysym, t_map *data, t_rayc *d)
{
	if (keysym == LEFT)
	{
		if (data->map[coord_to_pos(d->posX - d->planeX * MOVSTEP, d->posY, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX - d->planeX * \
		MOVSTEP, d->posY, data->nb_col)] != ' ')
			d->posX -= d->planeX * MOVSTEP;
		if (data->map[coord_to_pos(d->posX, d->posY - d->planeY * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX, d->posY - \
		d->planeY * MOVSTEP, data->nb_col)] != ' ')
			d->posY -= d->planeY * MOVSTEP;
	}
	else if (keysym == RIGHT)
	{
		if (data->map[coord_to_pos(d->posX + d->planeX * MOVSTEP, d->posY, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX + d->planeX * \
		MOVSTEP, d->posY, data->nb_col)] != ' ')
			d->posX += d->planeX * MOVSTEP;
		if (data->map[coord_to_pos(d->posX, d->posY + d->planeY * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posX, d->posY + \
		d->planeY * MOVSTEP, data->nb_col)] != ' ')
			d->posY += d->planeY * MOVSTEP;
	}
}

//Norm
static void	movement3(int keysym, t_rayc *d)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keysym == RLEFT)
	{
		oldDirX = d->dirX;
		oldPlaneX = d->planeX;
		d->dirX = d->dirX * cos(-ROTSTEP) - d->dirY * sin(-ROTSTEP);
		d->dirY = oldDirX * sin(-ROTSTEP) + d->dirY * cos(-ROTSTEP);
		d->planeX = d->planeX * cos(-ROTSTEP) - d->planeY * sin(-ROTSTEP);
		d->planeY = oldPlaneX * sin(-ROTSTEP) + d->planeY * cos(-ROTSTEP);
	}
	else if (keysym == RRIGHT)
	{
		oldDirX = d->dirX;
		oldPlaneX = d->planeX;
		d->dirX = d->dirX * cos(ROTSTEP) - d->dirY * sin(ROTSTEP);
		d->dirY = oldDirX * sin(ROTSTEP) + d->dirY * cos(ROTSTEP);
		d->planeX = d->planeX * cos(ROTSTEP) - d->planeY * sin(ROTSTEP);
		d->planeY = oldPlaneX * sin(ROTSTEP) + d->planeY * cos(ROTSTEP);
	}
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	t_rayc	*d;

	d = mlx->ray;
	if (keysym == XK_Escape)
		return (mlx_loop_end(mlx->ptr));
	if (keysym == FRONT || keysym == BACK)
		movement(keysym, mlx->data, d);
	else if (keysym == LEFT || keysym == RIGHT)
		movement2(keysym, mlx->data, d);
	else if (keysym == RLEFT || keysym == RRIGHT)
		movement3(keysym, d);
	return (0);
}