/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/28 19:59:34 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEBUG 1

//Keys
//Move
# define FRONT XK_z
# define BACK XK_s
# define LEFT XK_q
# define RIGHT XK_d
//rotation
# define RRIGHT XK_Right
# define RLEFT XK_Left

# define MOVSTEP 0.25
# define ROTSTEP 0.1

//Mlx
# define WIDTH 800
# define HEIGHT 600
# define NAME "cub3D"

//Errors
# define ARG_NBR "Need filename as argument\nExample: ./cub3D map.cub"
# define FNAME_FORMAT "Wrong file format, must be .cub"
# define OPEN "Could'nt open file"
# define READ "Could'nt read file"
# define CLOSE "Could'nt close file"
# define EMPTY "Empty file"
# define MALLOC "Malloc failed"
# define DOUBLE_TXT "Same texture appears twice in map"
# define MISS_TXT "Texture(s) missing"
# define INVALID_CHAR "Invalid character(s) in map"
# define INVALID_SIZE "Invalid size map"
# define NEW_LINE "New line in map"
# define VERT_UNCLOSED "Invalid character on vertical broder"
# define HORZ_UNCLOSED "Invalid character on horizontal broder"
# define UNCLOSED "Unclosed map"
# define DBL_STRT "Multiple start position"
# define NO_STRT "No start position"
# define MLX_INIT "Mlx init failed"
# define WIN_INIT "Mlx new window failed"
# define IMG_INIT "Mlx new image failed"
# define XPM_IMG "Mlx xpm file to image failed"
# define FLCE "Wrong format for floor or ceiling expected (0,0,0 to 255,255,255)"

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
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_map;

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
//FC color of Floor and Ceiling
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	screen;
	t_img	textures[4];
	int		FC[2];
	t_map	*data;
	unsigned int	frames;
}	t_mlx;

//PARSING
//parsing_textures.c
int				wrong_filename(char *filename);
int				read_file(char *filename, t_map *data);
int				get_texture_paths(t_map *data);
//parsing_map.c
int				invalid_char(t_map *data);
int				size_map(t_map *data);
int				get_map(t_map *data);
int				closed_map(t_map *data);
//parsing_mlx.c
int				get_textures(t_map *data, t_mlx *mlx);
int				init_mlx(t_mlx *mlx, t_map *data);

//MLX
//mlx_utils.c
int				handle_keypress(int keysym, t_mlx *mlx);
int				cross_press(t_mlx *mlx);
void			img_pix_put(t_img *img, int x, int y, unsigned int color);
unsigned int	get_img_color(t_img *img, int x, int y);
//render.c
int				render_screen(t_mlx *mlx);

//UTILS
//
int				print_err(char *fi, int li, const char *fu, char *str);
//data_utils.c
void			init_all(t_map *data, t_mlx *mlx);
int				free_all(t_map *data, t_mlx *mlx, int ret);
//convert_pos_x_y.c
int				pos_to_x(int pos, int row_len);
int				pos_to_y(int pos, int row_len);
int				coord_to_pos(int x, int y, int row_len);

#endif
