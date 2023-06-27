/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:05:27 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/27 14:55:59 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keysym, t_mlx *mlx)
{
	t_map	*d;

	d = mlx->data;
	if (keysym == XK_Escape)
		return (mlx_loop_end(mlx->ptr));
	if (keysym == FRONT)
	{
		if (d->map[coord_to_pos(d->posX + d->dirX * MOVSTEP, d->posY, d->nb_col)] != '1')
			d->posX += d->dirX * MOVSTEP;
		if (d->map[coord_to_pos(d->posX, d->posY + d->dirY * MOVSTEP, d->nb_col)] != '1')
			d->posY += d->dirY * MOVSTEP;
	}
	else if (keysym == BACK)
	{
		if (d->map[coord_to_pos(d->posX - d->dirX * MOVSTEP, d->posY, d->nb_col)] != '1')
			d->posX -= d->dirX * MOVSTEP;
		if (d->map[coord_to_pos(d->posX, d->posY - d->dirY * MOVSTEP, d->nb_col)] != '1')
			d->posY -= d->dirY * MOVSTEP;
	}
	else if (keysym == LEFT)
	{

	}
	else if (keysym == RIGHT)
	{

	}
	else if (keysym == RRIGHT)
	{
		double oldDirX = d->dirX;
		d->dirX = d->dirX * cos(ROTSTEP) - d->dirY * sin(ROTSTEP);
		d->dirY = oldDirX * sin(ROTSTEP) + d->dirY * cos(ROTSTEP);
		double oldPlaneX = d->planeX;
		d->planeX = d->planeX * cos(ROTSTEP) - d->planeY * sin(ROTSTEP);
		d->planeY = oldPlaneX * sin(ROTSTEP) + d->planeY * cos(ROTSTEP);
	}
	else if (keysym == RLEFT)
	{
		double oldDirX = d->dirX;
		d->dirX = d->dirX * cos(-ROTSTEP) - d->dirY * sin(-ROTSTEP);
		d->dirY = oldDirX * sin(-ROTSTEP) + d->dirY * cos(-ROTSTEP);
		double oldPlaneX = d->planeX;
		d->planeX = d->planeX * cos(-ROTSTEP) - d->planeY * sin(-ROTSTEP);
		d->planeY = oldPlaneX * sin(-ROTSTEP) + d->planeY * cos(-ROTSTEP);
	}
	render_screen(mlx);
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

	//if (color != 4278190080) // transparence (inutile ?)
	//{
		ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)ptr = color;
	//}
}

unsigned int	get_img_color(t_img *img, int x, int y)
{
	char	*ptr;

	ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)ptr);
}