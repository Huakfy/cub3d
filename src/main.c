/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/28 20:06:28 by mjourno          ###   ########.fr       */
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

void	print_map_debug(t_map *data) {
	int	i = 0;
	while (data->map[i]){
		if (i != 0 && i % data->nb_col == 0)
			printf("\n");
		printf("%c", data->map[i]);
		i++;
	}
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

	//print_map_debug(data);//

	if (get_textures(data, mlx))
		return (1);

	//free unneeded data
	free(data->file);
	data->file = NULL;
	int	i;
	i = -1;
	while (++i < 6)
	{
		free(data->textures[i]);
		data->textures[i] = NULL;
	}

	if (init_mlx(mlx, data))
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
