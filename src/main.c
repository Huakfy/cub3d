/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:09:18 by mjourno           #+#    #+#             */
/*   Updated: 2023/06/23 12:21:06 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	print_err(char *file, int line, const char *func, char *str)
{
	if (DEBUG)
		printf(YELLOW"File: %s line: %d function: %s\n"DEF, file, line, func);
	printf(RED"%s\n"DEF, str);
	return (1);
}

int	wrong_filename(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (ft_strcmp(filename + (i - 4), ".cub"))
		return (1);
	return (0);
}

int	parsing(int argc, char **argv)
{
	if (argc != 2)
		return (print_err(__FILE__, __LINE__, __func__, ARG_NBR));
	if (wrong_filename(argv[1]))
		return (print_err(__FILE__, __LINE__, __func__, FNAME_FORMAT));
	return (0);
}

int	main(int argc, char **argv)
{
	if (!parsing(argc, argv))
		return (1);
	return (0);
}
