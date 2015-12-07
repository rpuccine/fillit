/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 19:14:17 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/06 22:17:57 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			parse(t_sys *sys, int argc, char **argv)
{
	int		fd;
	char	*buff;
	int		ret;
	int		offset;

	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (1);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (1);
	offset = 0;
	while ((ret = read(fd, buff + offset, BUFF_SIZE)) > 0)
	{
		offset += ret;
		if (offset > 545)
			return (1);
	}
	if (ret < 0)
		return (1);
	buff[offset] = '\0';
	if (fillMap(sys, buff, offset))
		return (1);
	return (0);
}

int			fillMap(t_sys *sys, char *str, int len)
{
	int		i;
	int		j;
	int		k;
	int		offset;

	sys->nb_tetri = getNbTetri(len);
	if (!(sys->lst_tetri =
		(t_tetri *)malloc(sizeof(t_tetri) * sys->nb_tetri)))
		return (1);
	offset = 0;
	i = 0;
	while (i < sys->nb_tetri)
	{
		if (verifChar(str + offset))
			return (1);
		if (setTetri(sys, str + offset, i))
			return (1);
		offset += 20;
		if (i < sys->nb_tetri - 1)
		{
			if (str[offset] != '\n')
				return (1);
		}
		offset++;
		i++;
	}
	return (0);
}

int			setTetri(t_sys *sys, char *str, int cur)
{

}

int			verifChar(char *file)
{
	int		i;
	int		j;
	int		cub;

	i = 0;
	cub = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (file[i * 5 + j] != '.' && file[i * 5 + j] != '#')
				return (1);
			if (file[i * 5 + j] == '#')
				cub++;
			j++;
		}
		if (file[i * 5 + j] != '\n')
			return (1);
		i++;
	}
	if (cub != 4)
		return (1);
	return (0);
}

int			getNbTetri(int len)
{
	int nb_tetri;

	nb_tetri = len / 20;
	if (nb_tetri >= 22)
		nb_tetri--;
	return (nb_tetri);
}

