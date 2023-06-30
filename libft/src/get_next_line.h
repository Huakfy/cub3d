/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjourno <mjourno@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:11:18 by echapus           #+#    #+#             */
/*   Updated: 2023/06/30 15:35:24 by mjourno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
	struct s_list_gnl	*prev;
}					t_list_gnl;

int		free_list_gnl(t_list_gnl **list);
int		how_many(t_list_gnl *list, char **line);
int		make_line(t_list_gnl *list, char **line);
int		new_line(t_list_gnl *list);
int		add_to_list_gnl(t_list_gnl **list, char *buf);
int		write_in_list_gnl(int fd, t_list_gnl **list);
int		clear_list_gnl(t_list_gnl **list);
char	*get_next_line(int fd);

#endif
