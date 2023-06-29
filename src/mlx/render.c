/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:15:17 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/29 12:53:44 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	raycasting(t_mlx *mlx, t_map *data, t_rayc *ray)
{
	int	x = 0;
	while (x < WIDTH)
	{
		double	cameraX = 2 * x / (double)WIDTH - 1;
		double	rayDirX = ray->dirX + ray->planeX * cameraX;
		double	rayDirY = ray->dirY + ray->planeY * cameraX;

		int	mapX = (int)ray->posX;
		int	mapY = (int)ray->posY;

		double deltaDistX;
		if (!rayDirX)
			deltaDistX = 1e30;
		else if (rayDirX < 0)
			deltaDistX = -1 * (1 / rayDirX);
		else
			deltaDistX = 1 / rayDirX;

		double deltaDistY;
		if (!rayDirY)
			deltaDistY = 1e30;
		else if (rayDirY < 0)
			deltaDistY = -1 * (1 / rayDirY);
		else
			deltaDistY = 1 / rayDirY;

		double sideDistX;
		double sideDistY;
		int	stepX;
		int	stepY;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (ray->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (ray->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray->posY) * deltaDistY;
		}

		int	hit = 0;
		int	side;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[coord_to_pos(mapX, mapY, data->nb_col)] == '1')
				hit = 1;
		}

		double	perpWallDist;
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else		perpWallDist = (sideDistY - deltaDistY);

		int	lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		double	wallX;
		if (side == 0)	wallX = ray->posY + perpWallDist * rayDirY;
		else			wallX = ray->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int	texX = (int)(wallX * mlx->textures[0].width);
		if(side == 0 && rayDirX > 0) texX = mlx->textures[0].width - texX - 1;
		if(side == 1 && rayDirY < 0) texX = mlx->textures[0].width - texX - 1;

		double	step = 1.0 * mlx->textures[0].height / lineHeight;

		double	texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

		if (side == 0 && rayDirX > 0)
			side = 1;
		else if (side == 1 && rayDirY > 0)
			side = 2;
		else if (side == 1 && rayDirY < 0)
			side = 3;

		for (int y = 0; y < HEIGHT; y++)
		{
			if (y < drawStart)
			{
				img_pix_put(&mlx->screen, x, y, mlx->FC[1]);
				continue;
			}
			else if (y >= drawEnd)
			{
				img_pix_put(&mlx->screen, x, y, mlx->FC[0]);
				continue;
			}
			int	texY = (int)texPos & (mlx->textures[0].height - 1);
			texPos += step;
			int	color;

			color = *(unsigned int *)(mlx->textures[side].addr + (mlx->textures[side].line_len * texY + texX * (mlx->textures[side].bpp / 8)));
			img_pix_put(&mlx->screen, x, y, color);
		}
		x++;
	}
	return (0);
}

int	render_screen(t_mlx *mlx)
{
	raycasting(mlx, mlx->data, mlx->ray);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}