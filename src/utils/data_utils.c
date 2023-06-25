/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:45:06 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/26 00:21:52 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_map *data, t_mlx *mlx)
{
	int	i;

	data->file = NULL;
	i = -1;
	while (++i < 6)
		data->textures[i] = NULL;
	data->txt_end = 0;
	data->nb_col = 0;
	data->nb_line = 0;
	data->map = NULL;
	data->start_pos = 0;
	data->start_dir = 0;

	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->screen.img = NULL;
	mlx->screen.addr = NULL;
	mlx->screen.width = 0;
	mlx->screen.height = 0;
	i = -1;
	while (++i < 4)
	{
		mlx->textures[i].img = NULL;
		mlx->textures[i].addr = NULL;
		mlx->screen.width = 0;
		mlx->screen.height = 0;
	}
	mlx->FC[0] = 0;
	mlx->FC[1] = 0;
}

int	free_all(t_map *data, t_mlx *mlx, int ret)
{
	int	i;

	if (data->file)
		free(data->file);
	i = -1;
	while (++i < 6)
		if (data->textures[i])
			free(data->textures[i]);
	if (data->map)
		free(data->map);

	i = -1;
	while (++i < 4)
		if (mlx->textures[i].img)
			mlx_destroy_image(mlx->ptr, mlx->textures[i].img);
	if (mlx->screen.img)
		mlx_destroy_image(mlx->ptr, mlx->screen.img);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	return (ret);
}
