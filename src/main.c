/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 15:10:33 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	print_err(char *fi, int li, const char *fu, char *str)
{
	if (DEBUG)
		printf(YELLOW"File: %s | Line: %d | Function: %s\n"DEF, fi, li, fu);
	printf(RED"Error: %s\n"DEF, str);
	return (1);
}

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

int	parsing(t_cub3D *data, int argc, char **argv)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]))
		return (print_err(__FILE__, __LINE__, __func__, FNAME_FORMAT));
	if (read_file(argv[1], data))
		return (1);
	printf("%s\n", data->map);
	free(data->map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3D	data;

	if (!parsing(&data, argc, argv))
		return (1);
	return (0);
}
