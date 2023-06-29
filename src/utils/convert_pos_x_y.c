/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pos_x_y.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:50:52 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/29 12:18:58 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
