/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:47:08 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/24 11:34:48 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Checks if map characters are in "0 1 N S E W space \n"
static int	invalid_char(t_cub3D *data)
{
	int	i;

	i = data->txt_end;
	while (data->file[i] && ((9 <= data->file[i] && data->file[i] <= 13) || \
	data->file[i] == 20))
		i++;
	data->txt_end = i;
	while (data->file[i])
	{
		if (data->file[i] != '0' && data->file[i] != '1' && data->file[i] != 'N' \
		&& data->file[i] != 'S' && data->file[i] != 'E' && data->file[i] != 'W' \
		&& data->file[i] != ' ' && data->file[i] != '\n')
			return (print_err(__FILE__, __LINE__, __func__, INVALID_CHAR));
		if (data->file[i] && data->file[i] == '\n' && data->file[i - 1] == '\n')
			return (print_err(__FILE__, __LINE__, __func__, NEW_LINE));
		i++;
	}
	return (0);
}

void	size_map(t_cub3D *data)
{
	int	i;
	int	j;

	i = data->txt_end;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i + j] && data->file[i + j] != '\n')
			j++;
		if (j > data->nb_col)
			data->nb_col = j;
		i += j;
		if (data->file[i] && data->file[i] == '\n')
			data->nb_line++;
		if (data->file[i])
			i++;
	}
	data->nb_line ++;
}

void	debug(t_cub3D *data)//debug
{
	int	i = 0;
	while (data->map[i])
	{
		if (i && i % data->nb_col == 0)
			printf("\n");
		printf("%c", data->map[i]);
		i++;
	}
	printf("\n");
}

int	get_map(t_cub3D *data)
{
	int	i;
	int	j;
	int	len;

	i = data->txt_end;
	j = 0;
	len = 0;
	while (data->file[i])
	{
		if (data->file[i] == '\n' && i++)
		{
			while (len++ < data->nb_col)
				data->map[j++] = ' ';
			len = 0;
			continue ;
		}
		else
			data->map[j++] = data->file[i++];
		len++;
	}
	while (len++ < data->nb_col)
		data->map[j++] = ' ';
	data->map[j] = '\0';
	return (0);
}

int	parsing_map(t_cub3D *data)
{
	if (invalid_char(data))
		return (1);
	size_map(data);
	if (data->nb_line < 3 || data->nb_col < 3)
		return (print_err(__FILE__, __LINE__, __func__, INVALID_SIZE));
	data->map = malloc(sizeof(char) * ((data->nb_col * data->nb_line) + 1));
	if (!data->map)
		return (print_err(__FILE__, __LINE__, __func__, MALLOC));
	if (get_map(data))
		return (1);
	debug(data);
	return (0);
}
