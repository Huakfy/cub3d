/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:33:05 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 16:08:04 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	norm1(t_rayc *ray, int x)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = (int)ray->posX;
	ray->mapY = (int)ray->posY;
	if (!ray->rayDirX)
		ray->deltaDistX = 1e30;
	else if (ray->rayDirX < 0)
		ray->deltaDistX = -1 * (1 / ray->rayDirX);
	else
		ray->deltaDistX = 1 / ray->rayDirX;
	if (!ray->rayDirY)
		ray->deltaDistY = 1e30;
	else if (ray->rayDirY < 0)
		ray->deltaDistY = -1 * (1 / ray->rayDirY);
	else
		ray->deltaDistY = 1 / ray->rayDirY;
}

static void	norm2(t_rayc *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

static void	norm3(t_rayc *ray, t_map *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (data->map[coord_to_pos(ray->mapX, ray->mapY, data->nb_col)] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
}

static void	norm4(t_rayc *ray)
{
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	if (ray->side == 0)
		ray->wallX = ray->posY + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = ray->posX + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor((ray->wallX));
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
	print_square(mlx, 16777215, (ray->posX - 0.5) * 8, (ray->posY - 0.5) * 8);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}
