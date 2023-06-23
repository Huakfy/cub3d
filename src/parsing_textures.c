/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:16:10 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 22:00:05 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
static int	len_map(char *filename)
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
int	read_file(char *filename, t_cub3D *data) //revoir si stdin
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
//only called in get_texture_paths so static
static int	fname(t_cub3D *data, int *i, int skip, int text)
{
	int	j;

	if (data->textures[text])
		return (print_err(__FILE__, __LINE__, __func__, DOUBLE_TXT));
	j = 0;
	while (data->map[*i + j + skip] && data->map[*i + j + skip] != '\n')
		j++;
	data->textures[text] = ft_substr(data->map, *i + skip, j);
	if (!data->textures[text])
		return (print_err(__FILE__, __LINE__, __func__, MALLOC));
	*i += j + skip;
	return (0);
}

//Get each texture path (Fuck la norme)
int	get_texture_paths(t_cub3D *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		if ((!ft_strncmp(data->map + i, "NO ", 3) && fname(data, &i, 3, 0)) ||\
		 (!ft_strncmp(data->map + i, "SO ", 3) && fname(data, &i, 3, 1)) ||\
		 (!ft_strncmp(data->map + i, "WE ", 3) && fname(data, &i, 3, 2)) ||\
		 (!ft_strncmp(data->map + i, "EA ", 3) && fname(data, &i, 3, 3)) ||\
		 (!ft_strncmp(data->map + i, "F ", 2) && fname(data, &i, 2, 4)) ||\
		 (!ft_strncmp(data->map + i, "C ", 2) && fname(data, &i, 2, 5)))
				return (1);
		else if (data->map[i])
			i++;
		if (!data->txt_end && data->textures[0] && data->textures[1] && \
		data->textures[2] && data->textures[3] && data->textures[4] && \
		data->textures[5])
			data->txt_end = i;
	}
	i = -1;
	while (++i < 6)
		if (!data->textures[i])
			return (print_err(__FILE__, __LINE__, __func__, MISS_TXT));
	return (0);
}
