/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:10:11 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 19:59:35 by mjourno          ###   ########.fr       */
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
}	t_cub3D;

#endif
