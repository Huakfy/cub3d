/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:05:27 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/29 12:52:24 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Norm
static void	movement(int keysym, t_map *data, t_rayc *d)
{
	if (keysym == FRONT)
	{
		if (data->map[coord_to_pos(d->posX + d->dirX * MOVSTEP, d->posY + \
		d->dirY * MOVSTEP, data->nb_col)] == '1')
			return ;
		d->posX += d->dirX * MOVSTEP;
		d->posY += d->dirY * MOVSTEP;
	}
	else if (keysym == BACK)
	{
		if (data->map[coord_to_pos(d->posX - d->dirX * MOVSTEP, d->posY - \
		d->dirY * MOVSTEP, data->nb_col)] == '1')
			return ;
		d->posX -= d->dirX * MOVSTEP;
		d->posY -= d->dirY * MOVSTEP;
	}
	else if (keysym == LEFT)
	{
		if (data->map[coord_to_pos(d->posX - d->planeX * MOVSTEP, d->posY - \
		d->planeY * MOVSTEP, data->nb_col)] == '1')
				return ;
		d->posX -= d->planeX * MOVSTEP;
		d->posY -= d->planeY * MOVSTEP;
	}

}

//Norm
static void	movement2(int keysym, t_map *data, t_rayc *d)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keysym == RIGHT)
	{
		if (data->map[coord_to_pos(d->posX + d->planeX * MOVSTEP, d->posY + \
		d->planeY * MOVSTEP, data->nb_col)] == '1')
			return ;
		d->posX += d->planeX * MOVSTEP;
		d->posY += d->planeY * MOVSTEP;
	}
	if (keysym == RLEFT)
	{
		oldDirX = d->dirX;
		oldPlaneX = d->planeX;
		d->dirX = d->dirX * cos(-ROTSTEP) - d->dirY * sin(-ROTSTEP);
		d->dirY = oldDirX * sin(-ROTSTEP) + d->dirY * cos(-ROTSTEP);
		d->planeX = d->planeX * cos(-ROTSTEP) - d->planeY * sin(-ROTSTEP);
		d->planeY = oldPlaneX * sin(-ROTSTEP) + d->planeY * cos(-ROTSTEP);
	}
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	t_rayc	*d;
	double	oldDirX;
	double	oldPlaneX;

	d = mlx->ray;
	if (keysym == XK_Escape)
		return (mlx_loop_end(mlx->ptr));
	if (keysym == FRONT || keysym == BACK || keysym == LEFT)
		movement(keysym, mlx->data, d);
	else if (keysym == RIGHT || keysym == RLEFT)
		movement2(keysym, mlx->data, d);
	else if (keysym == RRIGHT)
	{
		oldDirX = d->dirX;
		oldPlaneX = d->planeX;
		d->dirX = d->dirX * cos(ROTSTEP) - d->dirY * sin(ROTSTEP);
		d->dirY = oldDirX * sin(ROTSTEP) + d->dirY * cos(ROTSTEP);
		d->planeX = d->planeX * cos(ROTSTEP) - d->planeY * sin(ROTSTEP);
		d->planeY = oldPlaneX * sin(ROTSTEP) + d->planeY * cos(ROTSTEP);
	}
	return (0);
}

int	cross_press(t_mlx *mlx)
{
	mlx_loop_end(mlx->ptr);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, unsigned int color)
{
	char	*ptr;

	ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)ptr = color;
}