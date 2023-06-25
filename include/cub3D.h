/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/25 11:22:40 by mjourno          ###   ########.fr       */
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
//# define GRAY		"\033[0;90m"
# define RED		"\033[0;91m"
//# define GREEN		"\033[0;92m"
# define YELLOW		"\033[0;93m"
//# define BLUE		"\033[0;94m"
//# define MAGENTA	"\033[0;95m"
//# define CYAN		"\033[0;96m"
//# define WHITE		"\033[0;97m"

//include lib
# include <stdio.h> //printf
# include <fcntl.h> //open

//include headers
# include "../libft/src/libft.h"

typedef struct s_cub3D
{
	char	*file;
	char	*textures[6]; // NO SO WE EA F C
	int		txt_end;
	int		nb_col;
	int		nb_line;
	char	*map;
	int		start_pos;
	char	start_dir;
}	t_cub3D;

//PARSING
//parsing_textures.c
int		wrong_filename(char *filename);
int		read_file(char *filename, t_cub3D *data);
int		get_texture_paths(t_cub3D *data);
//parsing_map.c
int		invalid_char(t_cub3D *data);
int		size_map(t_cub3D *data);
int		get_map(t_cub3D *data);
int		closed_map(t_cub3D *data);

//UTILS
//
int		print_err(char *fi, int li, const char *fu, char *str);
//data_utils.c
void	init_data(t_cub3D *data);
int		free_all(t_cub3D *data, int ret);
//convert_pos_x_y.c
int		pos_to_x(int pos, int row_len);
int		pos_to_y(int pos, int row_len);
int		coord_to_pos(int x, int y, int row_len);

#endif
