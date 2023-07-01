/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:05:27 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/01 17:13:09 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cross_press(t_mlx *mlx)
{
	mlx_loop_end(mlx->ptr);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, unsigned int color)
{
	char	*ptr;

	ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)ptr = color;
}