/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:47:43 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/28 15:59:49 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Atoi for color (return number between 0 to 255)
static int	get_color(char *color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (color[i] && color[i] != ',')
	{
		if (!('0' <= color[i] && color[i] <= '9') || i > 2)
		{
			print_err(__FILE__, __LINE__, __func__, FLCE);
			return (-1);
		}
		j = j * 10 + (color[i] - '0');
		i++;
	}
	if (j > 255 || i == 0)
	{
		print_err(__FILE__, __LINE__, __func__, FLCE);
			return (-1);
	}
	return (j);
}

//Gives power of ten of nb (nb between 0 to 250)
static int	get_power_ten(int nb)
{
	if (nb >= 100)
		return (3);
	else if (nb >= 10)
		return (2);
	else
		return (1);
}

//mlx->FC[k] gets color from RGB to int
//return (red << 16 | green << 8 | blue);
static int	get_FC(char *color, t_mlx *mlx, int k)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = get_color(color);
		if (j == -1)
			return (1);
		color += get_power_ten(j);
		if (*color == ',')
			color += 1;
		if (i == 0)
			mlx->FC[k] = j << 16;
		else if (i == 1)
			mlx->FC[k] += j << 8;
		else if (i == 2)
			mlx->FC[k] += j;
	}
	if (*color)
		return (print_err(__FILE__, __LINE__, __func__, FLCE));
	return (0);
}

//Get textures from xpm file to image and FC to int color
int	get_textures(t_map *data, t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		mlx->textures[i].img = mlx_xpm_file_to_image(mlx->ptr, \
		data->textures[i], &mlx->textures[i].width, &mlx->textures[i].height);
		if (!mlx->textures[i].img)
			return (print_err(__FILE__, __LINE__, __func__, XPM_IMG));
		mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img, \
		&mlx->textures[i].bpp, &mlx->textures[i].line_len, \
		&mlx->textures[i].endian);
	}
	if (get_FC(data->textures[4], mlx, 0))
		return (1);
	if (get_FC(data->textures[5], mlx, 1))
		return (1);
	return (0);
}

//Init mlx utils
int	init_mlx(t_mlx *mlx, t_map *data)
{
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, NAME);
	if (!mlx->win)
		return (print_err(__FILE__, __LINE__, __func__, WIN_INIT));
	mlx->screen.img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->screen.img)
		return (print_err(__FILE__, __LINE__, __func__, IMG_INIT));
	mlx->screen.addr = mlx_get_data_addr(mlx->screen.img, &mlx->screen.bpp, \
	&mlx->screen.line_len, &mlx->screen.endian);

	data->posX = pos_to_x(data->start_pos, data->nb_col) + 0.5;
	data->posY = pos_to_y(data->start_pos, data->nb_col) + 0.5;
	if (data->start_dir == 'N')
	{
		data->dirY = -1;
		data->planeX = 0.66;
	}
	else if (data->start_dir == 'S')
	{
		data->dirY = 1;
		data->planeX = -0.66;

	}
	else if (data->start_dir == 'W')
	{
		data->dirX = -1;
		data->planeY = -0.66;
	}
	else if (data->start_dir == 'E')
	{
		data->dirX = 1;
		data->planeY = 0.66;

	}

	//generate first image then only change it on key press
	render_screen(mlx);
	//mlx_loop_hook(mlx->ptr, &constant_loop, mlx); //for possible animations
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, ClientMessage, LeaveWindowMask, &cross_press, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}