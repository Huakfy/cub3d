/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 20:13:36 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Prints debug info if DEBUG = 1
//Then prints error
int	print_err(char *fi, int li, const char *fu, char *str)
{
	if (DEBUG)
		printf(YELLOW"File: %s | Line: %d | Function: %s\n"DEF, fi, li, fu);
	printf(RED"Error\n%s\n"DEF, str);
	return (1);
}

//Checks if filename ends in ".cub"
int	wrong_filename(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (ft_strcmp(filename + (i - 4), ".cub"))
		return (1);
	return (0);
}

//Goes 1 by 1 char throug the file to get its length
int	len_map(char *filename)
{
	int		i;
	int		fd;
	int		rd;
	char	garbage[1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_err(__FILE__, __LINE__, __func__, OPEN));
	i = 0;
	rd = 1;
	while (rd)
	{
		rd = read(fd, garbage, 1);
		if (rd == -1)
			return (print_err(__FILE__, __LINE__, __func__, READ));
		++i;
	}
	if (close(fd) == -1)
		return (print_err(__FILE__, __LINE__, __func__, CLOSE));
	if (i == 1)
		return (print_err(__FILE__, __LINE__, __func__, EMPTY));
	return (i - 1);
}

//Gets file content and put it in data->map
int	read_file(char *filename, t_cub3D *data)
{
	int	len;
	int	fd;

	len = len_map(filename);
	if (len == 1)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_err(__FILE__, __LINE__, __func__, OPEN));
	data->map = malloc(sizeof(char) * (len + 1));
	if (!data->map)
		return (print_err(__FILE__, __LINE__, __func__, MALLOC));
	if (read(fd, data->map, len) == -1)
		return (print_err(__FILE__, __LINE__, __func__, READ));
	data->map[len] = '\0';
	if (close(fd) == -1)
	{
		free(data->map);
		return (print_err(__FILE__, __LINE__, __func__, CLOSE));
	}
	return (0);
}

//Puts filename in the right data->texture
int	fname(t_cub3D *data, int i, int text)
{
	int	j;

	if (data->textures[text])
		return (print_err(__FILE__, __LINE__, __func__, DOUBLE_TXT));
	j = 0;
	while (data->map[i + j] && data->map[i + j] != '\n')
		j++;
	data->textures[text] = ft_substr(data->map, i, j);
	if (!data->textures[text])
		return (print_err(__FILE__, __LINE__, __func__, MALLOC));
	return (0);
}

//Get all texture paths
int	get_texture_paths(t_cub3D *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		if (!ft_strncmp(data->map + i, "NO ", 3) && fname(data, i + 3, 0))
				return (1);
		else if (!ft_strncmp(data->map + i, "SO ", 3) && fname(data, i + 3, 1))
			return (1);
		else if (!ft_strncmp(data->map + i, "WE ", 3) && fname(data, i + 3, 2))
			return (1);
		else if (!ft_strncmp(data->map + i, "EA ", 3) && fname(data, i + 3, 3))
			return (1);
		else if (!ft_strncmp(data->map + i, "F ", 2) && fname(data, i + 2, 4))
			return (1);
		else if (!ft_strncmp(data->map + i, "C ", 2) && fname(data, i + 2, 5))
			return (1);
		else
			i++;
	}
	i = -1;
	while (++i < 6)
		if (!data->textures[i])
			return (print_err(__FILE__, __LINE__, __func__, MISS_TXT));
	return (0);
}

int	parsing(t_cub3D *data, int argc, char **argv)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]))
		return (print_err(__FILE__, __LINE__, __func__, FNAME_FORMAT));
	if (read_file(argv[1], data))
		return (1);
	if (get_texture_paths(data))
		return (1);
	return (0);
}

void	init_data(t_cub3D *data)
{
	int	i;

	data->map = NULL;
	i = -1;
	while (++i < 6)
		data->textures[i] = NULL;
}

int	free_all(t_cub3D *data, int ret)
{
	int	i;

	if (data->map)
		free(data->map);
	i = -1;
	while (++i < 6)
		if (data->textures[i])
			free(data->textures[i]);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_cub3D	data;

	init_data(&data);
	if (parsing(&data, argc, argv))
		return (free_all(&data, 1));

	//debug texture name
	int	j = -1;
	while (++j < 6)
		if (data.textures[j])
			printf("%s\n", data.textures[j]);
	free_all(&data, 0);
}
