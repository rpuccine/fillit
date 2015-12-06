/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:26:45 by rpuccine          #+#    #+#             */
/*   Updated: 2015/01/21 11:38:18 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 100

typedef struct		s_fd
{
	char			*buf;
	int				fd;
}					t_fd;

t_list				*get_elem(t_list **list, int fd);

t_fd				*init_fd(t_list **list, int fd);

int					verif_endline(char **buf, char **line);

int					read_fd(t_fd *p_fd, char **line);

int					get_next_line(const int fd, char **line);

#endif
