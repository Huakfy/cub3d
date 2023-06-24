/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:45:06 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/24 13:34:51 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_data(t_cub3D *data)
{
	int	i;

	data->file = NULL;
	i = -1;
	while (++i < 6)
		data->textures[i] = NULL;
	data->txt_end = 0;
	data->nb_col = 0;
	data->nb_line = 0;
	data->map = NULL;
	data->start_pos = 0;
	data->start_dir = 0;
}

int	free_all(t_cub3D *data, int ret)
{
	int	i;

	if (data->file)
		free(data->file);
	i = -1;
	while (++i < 6)
		if (data->textures[i])
			free(data->textures[i]);
	if (data->map)
		free(data->map);
	return (ret);
}
