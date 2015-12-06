/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:32:30 by rpuccine          #+#    #+#             */
/*   Updated: 2015/02/18 19:20:50 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

t_list	*get_elem(t_list **list, int fd)
{
	t_list	*new;
	t_fd	*s_fd;

	if (!list)
		return (NULL);
	new = *list;
	while (new)
	{
		s_fd = (t_fd *)new->content;
		if (s_fd->fd == fd)
			return (new);
		new = new->next;
	}
	return (NULL);
}

t_fd	*init_fd(t_list **list, int fd)
{
	t_list	*new;
	t_fd	*fd_new;

	if ((new = get_elem(list, fd)))
		return ((t_fd *)new->content);
	if (!(fd_new = (t_fd *)malloc(sizeof(t_fd))))
		return (NULL);
	fd_new->fd = fd;
	if (!(fd_new->buf = ft_strnew(0)))
		return (NULL);
	if (!(new = ft_lstnew(fd_new, sizeof(t_fd))))
		return (NULL);
	free(fd_new);
	ft_lstappend(list, new);
	return ((t_fd *)new->content);
}

int		verif_endline(char **buf, char **line)
{
	char	*tmp;
	size_t	old_len;
	size_t	new_len;

	old_len = ft_strlen(*buf);
	tmp = NULL;
	if ((tmp = ft_strchr(*buf, '\n')))
	{
		new_len = ft_strlen(tmp);
		if (ft_strnconcat(line, *buf, old_len - new_len))
			return (-1);
		tmp = ft_strdup(tmp + 1);
		free(*buf);
		*buf = tmp;
		return (1);
	}
	else
	{
		if (!(*line = ft_strconcat(*line, *buf)))
			return (-1);
		ft_strclr(*buf);
		return (0);
	}
	return (-1);
}

int		read_fd(t_fd *p_fd, char **line)
{
	int		ret_verif;
	int		ret_read;
	char	*buffer;

	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((ret_verif = verif_endline(&buffer, line)) == 0)
	{
		if ((ret_read = read(p_fd->fd, buffer, BUFF_SIZE)) == -1)
			return (-1);
		else if (ret_read == 0)
		{
			free(buffer);
			if (**line)
				return (1);
			return (0);
		}
	}
	if (ret_verif == -1)
		return (-1);
	free(p_fd->buf);
	p_fd->buf = ft_strdup(buffer);
	free(buffer);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_fd			*p_fd;
	int				ret;

	if (!line)
		return (-1);
	*line = ft_strnew(0);
	if (!(p_fd = init_fd(&list, fd)))
		return (-1);
	if ((ret = verif_endline(&(p_fd->buf), line)) == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	return (read_fd(p_fd, line));
}
