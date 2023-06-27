/* ************************************************************************** */
/*																								    */
/*																		  :::		::::::::   */
/*   render.c														 :+:		:+:    :+:   */
/*																    +:+ +:+		   +:+     */
/*   By: mjourno <mjourno@student.42.fr>				+#+  +:+		 +#+		  */
/*																+#+#+#+#+#+   +#+		     */
/*   Created: 2023/06/26 11:15:17 by mjourno		     #+#    #+#				 */
/*   Updated: 2023/06/26 18:32:26 by mjourno		    ###   ########.fr		 */
/*																								    */
/* ************************************************************************** */

#include "cub3D.h"

//raycasting calcul a chaque ligne vertical de l'ecran donc plus opti d'avoir un jeu en 4:3
int	raycasting(t_mlx *mlx, t_map *data)
{
	int	x = 0;
	while (x < WIDTH)
	{
		double	cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;

		int	mapX = (int)data->posX;
		int	mapY = (int)data->posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX;
		if (!rayDirX)
			deltaDistX = 1e30;
		else if (rayDirX < 0)
			deltaDistX = -1 * (1 / rayDirX);
		else
			deltaDistX = 1 / rayDirX;

		double deltaDistY;
		if (!rayDirY)
			deltaDistY = 1e30;
		else if (rayDirY < 0)
			deltaDistY = -1 * (1 / rayDirY);
		else
			deltaDistY = 1 / rayDirY;

		double perpWallDist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[coord_to_pos(mapX, mapY, data->nb_col)] == '1')
				hit = 1;
		}
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else		perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		int	color = 16777215;

		if (side == 1) {color = color / 2;}

		for (int y = drawStart; y < drawEnd; y++)
			img_pix_put(&mlx->screen, x, y, color);
		x++;
	}
	(void)data;
	return (0);
}

int	render_screen(t_mlx *mlx)
{
	int	y = 0, x = 0;
	while (y < WIDTH){
		x = 0;
		while (x < HEIGHT){
			if (x < HEIGHT / 2)
				img_pix_put(&mlx->screen, y, x, mlx->FC[1]);
			else
				img_pix_put(&mlx->screen, y, x, mlx->FC[0]);
			x++;
		}
		y++;
	}
	raycasting(mlx, mlx->data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}