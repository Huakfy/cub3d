/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/25 12:32:34 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEBUG 1

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

//Colors
# define DEF		"\033[0;39m"
# define RED		"\033[0;91m"
# define YELLOW		"\033[0;93m"

//include lib
# include <stdio.h> //printf
# include <fcntl.h> //open

//include headers
# include "../libft/src/libft.h"

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

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

//textures: NO SO WE EA F C
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	screen;
	t_img	textures[6];
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

//UTILS
//
int		print_err(char *fi, int li, const char *fu, char *str);
//data_utils.c
void	init_data(t_map *data);
int		free_all(t_map *data, int ret);
//convert_pos_x_y.c
int		pos_to_x(int pos, int row_len);
int		pos_to_y(int pos, int row_len);
int		coord_to_pos(int x, int y, int row_len);

#endif
