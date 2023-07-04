/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:07:15 by mjourno           #+#    #+#             */
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

void	print_square(t_mlx *mlx, int color, int x, int y)
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

void	minimap(t_map *data, t_mlx *mlx)
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
			print_square(mlx, (mlx->fc[1] / 2) + 1, x, y);
			x += 8;
		}
		else
			x += 8;
		i++;
	}
	print_last_border(mlx, data, x, y);
}
