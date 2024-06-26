/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 15:41:06 by mjourno          ###   ########.fr       */
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

//Free unneded data
static void	free_unneeded(int i, t_map *data)
{
	int	j;

	if (i == 1)
	{
		free(data->file);
		data->file = NULL;
		return ;
	}
	else if (i == 2)
	{
		j = -1;
		while (++j < 6)
		{
			free(data->textures[j]);
			data->textures[j] = NULL;
		}
	}
}

//void	print_map_debug(t_map *data) {
//	int	i = 0;
//	while (data->map[i]){
//		if (i != 0 && i % data->nb_col == 0)
//			printf("\n");
//		printf("%c", data->map[i]);
//		i++;
//	}
//}

int	parsing(t_map *data, int argc, char **argv, t_mlx *mlx)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]) || read_file(argv[1], data) || \
	get_texture_paths(data) || invalid_char(data) || size_map(data) || \
	get_map(data) || closed_map(data))
		return (1);
	free_unneeded(1, data);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (print_err(__FILE__, __LINE__, __func__, MLX_INIT));
	if (get_textures(data, mlx) || init_mlx(mlx))
		return (1);
	free_unneeded(2, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	data;
	t_mlx	mlx;
	t_rayc	ray;

	init_all(&data, &mlx, &ray);
	if (parsing(&data, argc, argv, &mlx))
		return (free_all(&data, &mlx, 1));
	if (start_cub3d(&mlx, &data))
		return (1);
	free_all(&data, &mlx, 0);
}
