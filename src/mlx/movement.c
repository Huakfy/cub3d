/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:53:26 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/30 18:42:17 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Norm
void	movement(int keysym, t_map *data, t_rayc *d)
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
void	movement2(int keysym, t_map *data, t_rayc *d)
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
void	movement3(int keysym, t_rayc *d)
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
	if (keysym == XK_Escape)
		return (mlx_loop_end(mlx->ptr));

	if (keysym == FRONT)
		mlx->front = 1;
	else if (keysym == BACK)
		mlx->back = 1;
	else if (keysym == LEFT)
		mlx->left = 1;
	else if (keysym == RIGHT)
		mlx->right = 1;
	else if (keysym == RLEFT)
		mlx->rleft = 1;
	else if (keysym == RRIGHT)
		mlx->rright = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx *mlx)
{
	if (keysym == FRONT)
		mlx->front = 0;
	else if (keysym == BACK)
		mlx->back = 0;
	else if (keysym == LEFT)
		mlx->left = 0;
	else if (keysym == RIGHT)
		mlx->right = 0;
	else if (keysym == RLEFT)
		mlx->rleft = 0;
	else if (keysym == RRIGHT)
		mlx->rright = 0;
	return (0);
}