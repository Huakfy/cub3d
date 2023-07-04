/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:33:05 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 17:36:18 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	norm1(t_rayc *ray, int x)
{
	ray->camerax = 2 * x / (double)WIDTH - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	if (!ray->raydirx)
		ray->deltadistx = 1e30;
	else if (ray->raydirx < 0)
		ray->deltadistx = -1 * (1 / ray->raydirx);
	else
		ray->deltadistx = 1 / ray->raydirx;
	if (!ray->raydiry)
		ray->deltadisty = 1e30;
	else if (ray->raydiry < 0)
		ray->deltadisty = -1 * (1 / ray->raydiry);
	else
		ray->deltadisty = 1 / ray->raydiry;
}

static void	norm2(t_rayc *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - ray->posy) * ray->deltadisty;
	}
}

static void	norm3(t_rayc *ray, t_map *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (data->map[coord_to_pos(ray->mapx, ray->mapy, data->nb_col)] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
	ray->lineheight = (int)(HEIGHT / ray->perpwalldist);
}

static void	norm4(t_rayc *ray)
{
	ray->drawstart = -ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
	if (ray->side == 0)
		ray->wallx = ray->posy + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = ray->posx + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor((ray->wallx));
}

int	render_screen(t_mlx *mlx)
{
	int		x;
	t_map	*data;
	t_rayc	*ray;

	data = mlx->data;
	ray = mlx->ray;
	x = 0;
	while (x < WIDTH)
	{
		norm1(ray, x);
		norm2(ray);
		norm3(ray, data);
		norm4(ray);
		norm5(ray, mlx);
		norm6(ray, x, mlx);
		x++;
	}
	minimap(data, mlx);
	print_square(mlx, 16777215, (ray->posx - 0.5) * 8, (ray->posy - 0.5) * 8);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}
