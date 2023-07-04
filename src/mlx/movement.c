/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:53:26 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 17:31:28 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Norm
void	movement(int keysym, t_map *data, t_rayc *d)
{
	if (keysym == FRONT)
	{
		if (data->map[coord_to_pos(d->posx + d->dirx * MOVSTEP, d->posy, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx + d->dirx * \
		MOVSTEP, d->posy, data->nb_col)] != ' ')
			d->posx += d->dirx * MOVSTEP;
		if (data->map[coord_to_pos(d->posx, d->posy + d->diry * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx, d->posy + \
		d->diry * MOVSTEP, data->nb_col)] != ' ')
			d->posy += d->diry * MOVSTEP;
	}
	else if (keysym == BACK)
	{
		if (data->map[coord_to_pos(d->posx - d->dirx * MOVSTEP, d->posy, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx - d->dirx * \
		MOVSTEP, d->posy, data->nb_col)] != ' ')
			d->posx -= d->dirx * MOVSTEP;
		if (data->map[coord_to_pos(d->posx, d->posy - d->diry * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx, d->posy - \
		d->diry * MOVSTEP, data->nb_col)] != ' ')
			d->posy -= d->diry * MOVSTEP;
	}
}

//Norm
void	movement2(int keysym, t_map *data, t_rayc *d)
{
	if (keysym == LEFT)
	{
		if (data->map[coord_to_pos(d->posx - d->planex * MOVSTEP, d->posy, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx - d->planex * \
		MOVSTEP, d->posy, data->nb_col)] != ' ')
			d->posx -= d->planex * MOVSTEP;
		if (data->map[coord_to_pos(d->posx, d->posy - d->planey * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx, d->posy - \
		d->planey * MOVSTEP, data->nb_col)] != ' ')
			d->posy -= d->planey * MOVSTEP;
	}
	else if (keysym == RIGHT)
	{
		if (data->map[coord_to_pos(d->posx + d->planex * MOVSTEP, d->posy, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx + d->planex * \
		MOVSTEP, d->posy, data->nb_col)] != ' ')
			d->posx += d->planex * MOVSTEP;
		if (data->map[coord_to_pos(d->posx, d->posy + d->planey * MOVSTEP, \
		data->nb_col)] != '1' && data->map[coord_to_pos(d->posx, d->posy + \
		d->planey * MOVSTEP, data->nb_col)] != ' ')
			d->posy += d->planey * MOVSTEP;
	}
}

//Norm
void	movement3(int keysym, t_rayc *d)
{
	double	olddirx;
	double	oldplanex;

	if (keysym == RLEFT)
	{
		olddirx = d->dirx;
		oldplanex = d->planex;
		d->dirx = d->dirx * cos(-ROTSTEP) - d->diry * sin(-ROTSTEP);
		d->diry = olddirx * sin(-ROTSTEP) + d->diry * cos(-ROTSTEP);
		d->planex = d->planex * cos(-ROTSTEP) - d->planey * sin(-ROTSTEP);
		d->planey = oldplanex * sin(-ROTSTEP) + d->planey * cos(-ROTSTEP);
	}
	else if (keysym == RRIGHT)
	{
		olddirx = d->dirx;
		oldplanex = d->planex;
		d->dirx = d->dirx * cos(ROTSTEP) - d->diry * sin(ROTSTEP);
		d->diry = olddirx * sin(ROTSTEP) + d->diry * cos(ROTSTEP);
		d->planex = d->planex * cos(ROTSTEP) - d->planey * sin(ROTSTEP);
		d->planey = oldplanex * sin(ROTSTEP) + d->planey * cos(ROTSTEP);
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
