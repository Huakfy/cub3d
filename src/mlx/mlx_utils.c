/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:05:27 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/28 15:52:15 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keysym, t_mlx *mlx)
{
	t_map	*d;
	double	oldDirX;
	double	oldPlaneX;

	d = mlx->data;
	if (keysym == XK_Escape)
		return (mlx_loop_end(mlx->ptr));
	if (keysym == FRONT)
	{
		if (d->map[coord_to_pos(d->posX + d->dirX * MOVSTEP, d->posY + d->dirY * MOVSTEP, d->nb_col)] == '1')
			return (0);
		d->posX += d->dirX * MOVSTEP;
		d->posY += d->dirY * MOVSTEP;
	}
	else if (keysym == BACK)
	{
		if (d->map[coord_to_pos(d->posX - d->dirX * MOVSTEP, d->posY - d->dirY * MOVSTEP, d->nb_col)] == '1')
			return (0);
		d->posX -= d->dirX * MOVSTEP;
		d->posY -= d->dirY * MOVSTEP;
	}
	else if (keysym == LEFT)
	{
		if (d->map[coord_to_pos(d->posX + d->dirY * MOVSTEP, d->posY - d->dirX * MOVSTEP, d->nb_col)] == '1')
			return (0);
		d->posX += d->dirY * MOVSTEP;
		d->posY -= d->dirX * MOVSTEP;
	}
	else if (keysym == RIGHT)
	{
		if (d->map[coord_to_pos(d->posX - d->dirY * MOVSTEP, d->posY + d->dirX * MOVSTEP, d->nb_col)] == '1')
			return (0);
		d->posX -= d->dirY * MOVSTEP;
		d->posY += d->dirX * MOVSTEP;
	}
	else if (keysym == RLEFT)
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