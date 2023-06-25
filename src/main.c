/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/25 22:04:22 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Prints debug info if DEBUG = 1
//Then prints error
int	print_err(char *fi, int li, const char *fu, char *str)
{
	if (DEBUG)
		printf(YELLOW"File: %s | Line: %d | Function: %s\n"DEF, fi, li, fu);
	write(2, RED, ft_strlen(RED));
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	write(2, DEF, ft_strlen(DEF));
	return (1);
}

//PARSING
//✓ Check if 1 arg
//✓ Check if filename ends in ."cub"
//✓ Read file and put into string								!!!(Maybe comeback to it for stdin)!!!
//✓ Check if one and only one texture for each type NO SO WE EA F C (skip spaces not isspace)
//✓ Check if only valid characters in map 0 1 N S E W space
//✓ Check if map is closed
//✓ Put map into file, formated in rectangle
//✓ \n anywhere but not in map (checks if \n after \n)
//✓ Check if map is at end of file (i + 1 = NULL)
//✓ check only one N || S || W || E

//X Check if textures files exist or color exist

int	get_textures(t_map *data, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (i < 4)
	{
		mlx->textures[i].img = mlx_xpm_file_to_image(mlx->ptr, \
		data->textures[i], &mlx->textures[i].width, &mlx->textures[i].height);
		if (!mlx->textures[i].img)
			return (print_err(__FILE__, __LINE__, __func__, XPM_IMG));
	}
	return (0);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (print_err(__FILE__, __LINE__, __func__, MLX_INIT));
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, NAME);
	if (!mlx->win)
		return (print_err(__FILE__, __LINE__, __func__, WIN_INIT));
	mlx->screen.img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->screen.img)
		return (print_err(__FILE__, __LINE__, __func__, IMG_INIT));
	mlx->screen.addr = mlx_get_data_addr(mlx->screen.img, &mlx->screen.bpp, \
	&mlx->screen.line_len, &mlx->screen.endian);
	return (0);
}

int	parsing(t_map *data, int argc, char **argv, t_mlx *mlx)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]) || read_file(argv[1], data))
		return (1);
	if (get_texture_paths(data) || invalid_char(data) || size_map(data))
		return (1);
	if (get_map(data) || closed_map(data))
		return (1);
	if (init_mlx(mlx) || get_textures(data, mlx))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	data;
	t_mlx	mlx;

	init_data(&data, &mlx);
	if (parsing(&data, argc, argv, &mlx))
		return (free_all(&data, &mlx, 1));
	free_all(&data, &mlx, 0);
}
