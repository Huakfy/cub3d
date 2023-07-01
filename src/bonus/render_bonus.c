/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:33:05 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/01 17:01:44 by mjourno          ###   ########.fr       */
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
	if(ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
}

static void	norm4(t_rayc *ray)
{
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if(ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if(ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	if (ray->side == 0)
		ray->wallX = ray->posY + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = ray->posX + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor((ray->wallX));
}

static void	norm5(t_rayc *ray, t_mlx *mlx)
{
	if (ray->side == 1 && ray->rayDirY < 0)
	{
		ray->texX = mlx->textures[0].width - ray->texX - 1;
		ray->texX = (int)(ray->wallX * mlx->textures[0].width);
		ray->side = 0;
	}
	else if (ray->side == 1 && ray->rayDirY > 0)
	{
		ray->texX = mlx->textures[1].width - ray->texX - 1;
		ray->texX = (int)(ray->wallX * mlx->textures[1].width);
		ray->side = 1;
	}
	else if (ray->side == 0 && ray->rayDirX < 0)
	{
		ray->texX = mlx->textures[2].width - ray->texX - 1;
		ray->texX = (int)(ray->wallX * mlx->textures[2].width);
		ray->side = 2;
	}
	else if (ray->side == 0 && ray->rayDirX > 0)
	{
		ray->texX = mlx->textures[3].width - ray->texX - 1;
		ray->texX = (int)(ray->wallX * mlx->textures[3].width);
		ray->side = 3;
	}
}

static void	norm6(t_rayc *ray, int x, t_mlx *mlx)
{
	int	y;

	ray->step = 1.0 * mlx->textures[ray->side].height / ray->lineHeight;
	ray->texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * \
	ray->step;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->drawStart)
			img_pix_put(&mlx->screen, x, y, mlx->FC[1]);
		else if (y >= ray->drawEnd)
			img_pix_put(&mlx->screen, x, y, mlx->FC[0]);
		else
		{
			ray->texY = (int)ray->texPos & (mlx->textures[ray->side].height - \
			1);
			ray->texPos += ray->step;
			ray->color = *(unsigned int *)(mlx->textures[ray->side].addr + \
			(mlx->textures[ray->side].line_len * ray->texY + ray->texX * \
			(mlx->textures[ray->side].bpp / 8)));
			img_pix_put(&mlx->screen, x, y, ray->color);
		}
	}
}

static void	print_square(t_mlx *mlx, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8 && x < WIDTH && y < HEIGHT)
		{
			img_pix_put(&mlx->screen, j + x, i + y, color);
			j++;
		}
		i++;
	}
}

static void	print_last_border(t_mlx *mlx, t_map *data, int x, int y)
{
	print_square(mlx, 0, x, y);
	y += 8;
	x = 0;
	while (x < (data->nb_col + 1) * 8)
	{
		print_square(mlx, 0, x, y);
		x += 8;
	}
}

static void	minimap(t_map *data, t_mlx *mlx)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (data->map[i] && x < WIDTH && y < HEIGHT)
	{
		if (i && i % data->nb_col == 0)
		{
			print_square(mlx, 0, x, y);
			y += 8;
			x = 0;
		}
		if (data->map[i] == '1' || data->map[i] == ' ')
		{
			print_square(mlx, (mlx->FC[1] / 2) + 1, x, y);
			x += 8;
		}
		else
			x += 8;
		i++;
	}
	print_last_border(mlx, data, x, y);
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
