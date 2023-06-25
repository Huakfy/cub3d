/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:47:08 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/25 11:22:32 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Checks if map characters are in "0 1 N S E W space \n"
int	invalid_char(t_cub3D *data)
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

//Gets number og lines and columns and malloc the map
int	size_map(t_cub3D *data)
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
	if (data->nb_line < 3 || data->nb_col < 3)
		return (print_err(__FILE__, __LINE__, __func__, INVALID_SIZE));
	data->map = malloc(sizeof(char) * ((data->nb_col * data->nb_line) + 1));
	if (!data->map)
		return (print_err(__FILE__, __LINE__, __func__, MALLOC));
	return (0);
}

//Get map into data->map
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

//Checks around 0 or NSWE to see if map is closed
static int	check_around(t_cub3D *data, int i)
{
	int	x;
	int	y;

	x = pos_to_x(i, data->nb_col);
	y = pos_to_y(i, data->nb_col);

	if (!ft_strchr("01NSWE", data->map[coord_to_pos(x - 1, y, data->nb_col)]))
		return (1);
	if (!ft_strchr("01NSWE", data->map[coord_to_pos(x + 1, y, data->nb_col)]))
		return (1);
	if (!ft_strchr("01NSWE", data->map[coord_to_pos(x, y - 1, data->nb_col)]))
		return (1);
	if (!ft_strchr("01NSWE", data->map[coord_to_pos(x, y + 1, data->nb_col)]))
		return (1);
	return (0);
}

//Checks around 0 or NSWE to see if map is closed
//Also checks if one and only one start pos
int	closed_map(t_cub3D *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		if ((pos_to_x(i, data->nb_col) == 0 || pos_to_x(i, data->nb_col) == \
		data->nb_col - 1) && data->map[i] != '1' && data->map[i] != ' ')
			return (print_err(__FILE__, __LINE__, __func__, VERT_UNCLOSED));
		else if ((pos_to_y(i, data->nb_col) == 0 || pos_to_y(i, data->nb_col) \
		== data->nb_line - 1) && data->map[i] != '1' && data->map[i] != ' ')
			return (print_err(__FILE__, __LINE__, __func__, HORZ_UNCLOSED));
		else if ((ft_strchr("0NSWE", data->map[i])) && check_around(data, i))
			return (print_err(__FILE__, __LINE__, __func__, UNCLOSED));
		if (ft_strchr("NSWE", data->map[i]))
		{
			if (data->start_pos)
				return (print_err(__FILE__, __LINE__, __func__, DBL_STRT));
			data->start_pos = i;
			data->start_dir = data->map[i];
		}
		i++;
	}
	if (!data->start_pos)
		return (print_err(__FILE__, __LINE__, __func__, NO_STRT));
	return (0);
}

