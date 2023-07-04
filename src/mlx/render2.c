/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:04:34 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 16:06:21 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	norm5(t_rayc *ray, t_mlx *mlx)
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

void	norm6(t_rayc *ray, int x, t_mlx *mlx)
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
