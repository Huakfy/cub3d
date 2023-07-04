/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:04:34 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 17:37:07 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	norm5(t_rayc *ray, t_mlx *mlx)
{
	if (ray->side == 1 && ray->raydiry < 0)
	{
		ray->texx = mlx->textures[0].width - ray->texx - 1;
		ray->texx = (int)(ray->wallx * mlx->textures[0].width);
		ray->side = 0;
	}
	else if (ray->side == 1 && ray->raydiry > 0)
	{
		ray->texx = mlx->textures[1].width - ray->texx - 1;
		ray->texx = (int)(ray->wallx * mlx->textures[1].width);
		ray->side = 1;
	}
	else if (ray->side == 0 && ray->raydirx < 0)
	{
		ray->texx = mlx->textures[2].width - ray->texx - 1;
		ray->texx = (int)(ray->wallx * mlx->textures[2].width);
		ray->side = 2;
	}
	else if (ray->side == 0 && ray->raydirx > 0)
	{
		ray->texx = mlx->textures[3].width - ray->texx - 1;
		ray->texx = (int)(ray->wallx * mlx->textures[3].width);
		ray->side = 3;
	}
}

void	norm6(t_rayc *ray, int x, t_mlx *mlx)
{
	int	y;

	ray->step = 1.0 * mlx->textures[ray->side].height / ray->lineheight;
	ray->texpos = (ray->drawstart - HEIGHT / 2 + ray->lineheight / 2) * \
	ray->step;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->drawstart)
			img_pix_put(&mlx->screen, x, y, mlx->fc[1]);
		else if (y >= ray->drawend)
			img_pix_put(&mlx->screen, x, y, mlx->fc[0]);
		else
		{
			ray->texy = (int)ray->texpos & (mlx->textures[ray->side].height - \
			1);
			ray->texpos += ray->step;
			ray->color = *(unsigned int *)(mlx->textures[ray->side].addr + \
			(mlx->textures[ray->side].line_len * ray->texy + ray->texx * \
			(mlx->textures[ray->side].bpp / 8)));
			img_pix_put(&mlx->screen, x, y, ray->color);
		}
	}
}
