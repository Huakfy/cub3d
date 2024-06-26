/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/07/04 17:38:20 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEBUG 1

//Keys
//Move
# define FRONT	0x0077
# define BACK	0x0073
# define LEFT	0x0061
# define RIGHT	0x0064
//Rotate
# define RRIGHT	0xff53
# define RLEFT	0xff51
//Moving and rotation speed
# define MOVSTEP	0.15
# define ROTSTEP	0.05

//Mlx
# define WIDTH				1920
# define HEIGHT				1080
# define NAME				"cub3D"
# define REFRESH_RATE		1000
# define REFRESH_RATE_MOVE	1500

//Errors
# define ARG_NBR		"Need filename as argument\nExample: ./cub3D map.cub"
# define FNAME_FORMAT	"Wrong file format, must be .cub"
# define OPEN			"Could'nt open file"
# define READ			"Could'nt read file"
# define CLOSE			"Could'nt close file"
# define EMPTY			"Empty file"
# define MALLOC			"Malloc failed"
# define DOUBLE_TXT		"Same texture appears twice in map"
# define MISS_TXT		"Texture(s) missing"
# define INVALID_CHAR	"Invalid character(s) in map"
# define INVALID_SIZE	"Invalid size map"
# define NEW_LINE		"New line in map"
# define VERT_UNCLOSED	"Invalid character on vertical broder"
# define HORZ_UNCLOSED	"Invalid character on horizontal broder"
# define UNCLOSED		"Unclosed map"
# define DBL_STRT		"Multiple start position"
# define NO_STRT		"No start position"
# define MLX_INIT		"Mlx init failed"
# define WIN_INIT		"Mlx new window failed"
# define IMG_INIT		"Mlx new image failed"
# define XPM_IMG		"Mlx xpm file to image failed"
# define XPM_IMG_SIZE	"Textures aren't all the same size"
# define FLCE			"Wrong format for floor or ceiling"

//Colors
# define DEF		"\033[0;39m"
# define RED		"\033[0;91m"
# define YELLOW		"\033[0;93m"

//Lib
# include <stdio.h> //printf
# include <fcntl.h> //open
# include <X11/X.h> //event and masks
# include <X11/keysym.h> //keypress real names ex: XK_Escape
# include <math.h> //raycasting

//Headers
# include "libft.h" //libft
# include "mlx.h" //mlx

//textures: NO SO WE EA F C
typedef struct s_map
{
	char	*file;
	char	*textures[6];
	int		txt_end;
	int		nb_col;
	int		nb_line;
	char	*map;
	int		start_pos;
	char	start_dir;
}	t_map;

typedef struct s_rayc
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
	double			step;
	double			texpos;
	int				texy;
	unsigned int	color;
}	t_rayc;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

//textures: NO SO WE EA
//fc color of Floor and Ceiling
typedef struct s_mlx
{
	void			*ptr;
	void			*win;
	t_img			screen;
	t_img			textures[4];
	int				fc[2];
	unsigned int	frames;
	t_map			*data;
	t_rayc			*ray;
	int				front;
	int				back;
	int				left;
	int				right;
	int				rleft;
	int				rright;
}	t_mlx;

//PARSING
//parsing_textures.c
int		wrong_filename(char *filename);
int		read_file(char *filename, t_map *data);
int		get_texture_paths(t_map *data);
//parsing_map.c
int		invalid_char(t_map *data);
int		size_map(t_map *data);
int		get_map(t_map *data);
int		closed_map(t_map *data);
//parsing_mlx.c
int		get_textures(t_map *data, t_mlx *mlx);
int		init_mlx(t_mlx *mlx);

//MLX
//movement.c
int		handle_keypress(int keysym, t_mlx *mlx);
int		handle_keyrelease(int keysym, t_mlx *mlx);
void	movement(int keysym, t_map *data, t_rayc *d);
void	movement2(int keysym, t_map *data, t_rayc *d);
void	movement3(int keysym, t_rayc *d);
//mlx_utils.c
int		cross_press(t_mlx *mlx);
void	img_pix_put(t_img *img, int x, int y, unsigned int color);
//render.c
int		render_screen(t_mlx *mlx);
//render2.c
void	norm5(t_rayc *ray, t_mlx *mlx);
void	norm6(t_rayc *ray, int x, t_mlx *mlx);
//start_cub3d.c
int		start_cub3d(t_mlx *mlx, t_map *data);

//UTILS
//
int		print_err(char *fi, int li, const char *fu, char *str);
//data_utils.c
void	init_all(t_map *data, t_mlx *mlx, t_rayc *ray);
int		free_all(t_map *data, t_mlx *mlx, int ret);
//convert_pos_x_y.c
int		pos_to_x(int pos, int row_len);
int		pos_to_y(int pos, int row_len);
int		coord_to_pos(int x, int y, int row_len);

//BONUS
void	print_square(t_mlx *mlx, int color, int x, int y);
void	minimap(t_map *data, t_mlx *mlx);

#endif
