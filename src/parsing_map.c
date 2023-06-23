/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:47:08 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 22:01:08 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Checks if map characters are in "0 1 N S E W space \n"
static int	valid_chars(t_cub3D *data)
{
	int	i;

	i = data->txt_end;
	while (data->map[i])
	{
		if (data->map[i] != '0' && data->map[i] != '1' && data->map[i] != 'N' \
		&& data->map[i] != 'S' && data->map[i] != 'E' && data->map[i] != 'W' \
		&& data->map[i] != ' ' && data->map[i] != '\n')
			return (print_err(__FILE__, __LINE__, __func__, INVALID_CHAR));
		i++;
	}
	return (0);
}

//len_line
//int	i;
//int	j;

//i = data->txt_end;
//while (data->map[i])
//{
//	j = 0;
//	while (data->map[i + j] && data->map[i + j] != '\n')
//		j++;
//	if (j > data->len_line)
//		data->len_line = j;
//	i += j;
//	if (data->map[i])
//		i++;
//}

int	parsing_map(t_cub3D *data)
{
	if (!valid_chars(data))
		return (1);
	return (0);
}
