/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/26 11:01:31 by mjourno          ###   ########.fr       */
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

void	img_pix_put(t_img *img, int x, int y, unsigned int color)
{
	char	*ptr;

	if (color != 4278190080) // transparence (inutile ?)
	{
		ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)ptr = color;
	}
}

unsigned int	get_color(t_img *img, int x, int y)
{
	char	*ptr;

	ptr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)ptr);
}

int	constant_loop(t_mlx *mlx)
{
	int	i = 0, j = 0;
	while (i < WIDTH){
		j = 0;
		while (j < HEIGHT){
			img_pix_put(&mlx->screen, i, j, mlx->FC[0]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
		mlx_loop_end(mlx->ptr);
	return (0);
}

int	cross_press(t_mlx *mlx)
{
	mlx_loop_end(mlx->ptr);
	return (0);
}

int	parsing(t_map *data, int argc, char **argv, t_mlx *mlx)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]) || read_file(argv[1], data) || \
	get_texture_paths(data) || invalid_char(data) || size_map(data) || \
	get_map(data) || closed_map(data))
		return (1);
	free(data->file);
	data->file = NULL;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (print_err(__FILE__, __LINE__, __func__, MLX_INIT));
	if (get_textures(data, mlx) || init_mlx(mlx))
		return (1);
	return (0);
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
//✓ Check if textures files exist or color exist

int	main(int argc, char **argv)
{
	t_map	data;
	t_mlx	mlx;

	init_all(&data, &mlx);
	if (parsing(&data, argc, argv, &mlx))
		return (free_all(&data, &mlx, 1));
	free_all(&data, &mlx, 0);
}
