/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/24 13:53:18 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//Prints debug info if DEBUG = 1
//Then prints error
int	print_err(char *fi, int li, const char *fu, char *str)
{
	if (DEBUG)
		printf(YELLOW"File: %s | Line: %d | Function: %s\n"DEF, fi, li, fu);
	printf(RED"Error\n%s\n"DEF, str); //Revoir si print sur STDERR
	return (1);
}

//PARSING
//✓ Check if 1 arg
//✓ Check if filename ends in ."cub"
//✓ Read file and put into string !!!(Maybe comeback to it for stdin)!!!
//✓ Check if one and only one texture for each type
//✓ Check if only valid characters in map 0 1 N S E W space
//✓ Check if map is closed
//✓ Put map into file, formated in rectangle
//✓ \n anywhere but not in map
//✓ Check if map is at end of file (i + 1 = NULL) !!!RIEN APRES LA MAP!!!
//✓ check only one N || S || W || E

//X Check if textures files exist or color exist
//Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s) space or is space ?
//^Ignore isspace in textures^
int	parsing(t_cub3D *data, int argc, char **argv)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]))
		return (print_err(__FILE__, __LINE__, __func__, FNAME_FORMAT));
	if (read_file(argv[1], data))
		return (1);
	if (get_texture_paths(data))
		return (1);
	if (parsing_map(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3D	data;

	init_data(&data);
	if (parsing(&data, argc, argv))
		return (free_all(&data, 1));
	//debug texture name
	//int	j = -1;
	//while (++j < 6)
	//	if (data.textures[j])
	//		printf("%s\n", data.textures[j]);
	free_all(&data, 0);
}
