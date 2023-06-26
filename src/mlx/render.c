/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:15:17 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/26 11:43:01 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_screen(t_mlx *mlx)
{
	int	y = 0, x = 0;
	while (y < WIDTH){
		x = 0;
		while (x < HEIGHT){
			if (x < HEIGHT / 2)
				img_pix_put(&mlx->screen, y, x, mlx->FC[1]);
			else
				img_pix_put(&mlx->screen, y, x, mlx->FC[0]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}