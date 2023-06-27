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
	double	posX = pos_to_x(data->start_pos, data->nb_col);
	double	posY = pos_to_y(data->start_pos, data->nb_col);
	double	dirX = 0, dirY = 0; // change this after start
	if (data->start_dir == 'N')
		dirY = -0.66;
	else if (data->start_dir == 'S')
		dirY = 0.66;
	else if (data->start_dir == 'W')
		dirX = -0.66;
	else if (data->start_dir == 'E')
		dirX = 0.66;
	double	planeX = 0.66, planeY = 0; //have to be perpendicular tu dir
	//double posX = 22, posY = 12;  //x and y start position
	//double dirX = -1, dirY = 0; //initial direction vector
	//double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	int	x = 0;
	while (x < WIDTH)
	{
		//calculate ray position and direction
		double	cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int	mapX = (int)posX;
		int	mapY = (int)posY;

		//length of ray from one x or y-side to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from current position to next x or y-side
		//double deltaDistX = (rayDirX == 0) ? 1e30 : abs((int)(1 / rayDirX));
		double deltaDistX;
		if (!rayDirX)
			deltaDistX = 1e30;
		else if (rayDirX < 0)
			deltaDistX = -1 * (1 / rayDirX);
		else
			deltaDistX = 1 / rayDirX;
		//double deltaDistY = (rayDirY == 0) ? 1e30 : abs((int)(1 / rayDirY));
		double deltaDistY;
		if (!rayDirY)
			deltaDistY = 1e30;
		else if (rayDirY < 0)
			deltaDistY = -1 * (1 / rayDirY);
		else
			deltaDistY = 1 / rayDirY;

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int	stepX;
		int	stepY;

		int	hit = 0; //was there a wall hit?
		int	side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
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
			//Check if ray has hit a wall
			if (data->map[coord_to_pos(mapX, mapY, data->nb_col)] > '0')
			//if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else		perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		//choose wall color
		int	color = 255;
		//int	color;
		//switch(worldMap[mapX][mapY])
		//{
		//	case 1:  color = 16711680;	break; //red
		//	case 2:  color = 65280;  break; //green
		//	case 3:  color = 255;   break; //blue
		//	case 4:  color = 16777215;  break; //white
		//	default: color = 16768256; break; //yellow
		//}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		//printf("color %d x %d start %d end %d map[xy] %c\n", color, x, drawStart, drawEnd, data->map[coord_to_pos(mapX, mapY, data->nb_col)]);
		for (int y = drawStart; y < drawEnd; y++)
			img_pix_put(&mlx->screen, x, y, color);
		x++;
	}
	(void)data;
	return (0);
}

int	render_screen(t_mlx *mlx)
{
	//int	y = 0, x = 0;
	//while (y < WIDTH){
	//	x = 0;
	//	while (x < HEIGHT){
	//		if (x < HEIGHT / 2)
	//			img_pix_put(&mlx->screen, y, x, mlx->FC[1]);
	//		else
	//			img_pix_put(&mlx->screen, y, x, mlx->FC[0]);
	//		x++;
	//	}
	//	y++;
	//}
	raycasting(mlx, mlx->data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}