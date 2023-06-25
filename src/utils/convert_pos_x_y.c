/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pos_x_y.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:50:52 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/25 12:40:40 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	pos_to_x(int pos, int nb_col)
{
	return (pos % nb_col);
}

int	pos_to_y(int pos, int nb_col)
{
	return (pos / nb_col);
}

int	coord_to_pos(int x, int y, int nb_col)
{
	return (x + y * nb_col);
}

//int	change_pos(int pos, char *map, int value, int nb_col)
//{
//	int	x;
//	int	y;
//	int	next_pos;

//	x = pos_to_x(pos, nb_col);
//	y = pos_to_y(pos, nb_col);
//	if (value == 1)
//		next_pos = coord_to_pos(x + 1, y, nb_col);
//	if (value == 2)
//		next_pos = coord_to_pos(x - 1, y, nb_col);
//	if (value == 3)
//		next_pos = coord_to_pos(x, y + 1, nb_col);
//	if (value == 4)
//		next_pos = coord_to_pos(x, y - 1, nb_col);
//	if (map[next_pos] != '1')
//		return (next_pos);
//	return (0);
//}
