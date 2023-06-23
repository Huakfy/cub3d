/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 21:59:47 by mjourno          ###   ########.fr       */
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
	char	*map;
	char	*textures[6]; // NO SO WE EA F C
	int		txt_end;
	int		len_line;
}	t_cub3D;

//PARSING
//parsing_textures.c
int	wrong_filename(char *filename);
int	read_file(char *filename, t_cub3D *data);
int	get_texture_paths(t_cub3D *data);
//parsing_map.c
int	parsing_map(t_cub3D *data);

//UTILS
//
int	print_err(char *fi, int li, const char *fu, char *str);
//data_utils.c
void	init_data(t_cub3D *data);
int	free_all(t_cub3D *data, int ret);

#endif
