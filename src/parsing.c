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
	while ((ret = read(fd, buff + offset, BUFF_SIZE - offset)) > 0)
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
	t_sysCub	sysCub;
	int			i;
	int			j;

	ft_bzero((void*)&sysCub, sizeof(t_sysCub));
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			j = 0;
			while (j < 4)
			{
				sysCub.lst[0].verif[j] = TRUE;
				if (!backVerif(&sysCub, i, j, str))
				{
					buildTetri(sys, &sysCub, str, cur);
					return (0);
				}
				j++;
			}
			return (1);
		}
		i++;
	}
	return (1);
}

void		buildTetri(t_sys *sys, t_sysCub *sysCub, char *str, int cur)
{
	int		start;
	int		i;
	int		j;
	t_tetri	*t;

	t = sys->lst_tetri + cur;
	t->x = ft_max(sysCub->nbVerif[0], sysCub->nbVerif[2]);
	t->y = sysCub->nbVerif[1];
	start = getStart(sysCub->lst);
	t->in = (t_ch *)malloc(sizeof(t_ch) * (t->x * t->y));
	i = 0;
	while (i < t->y)
	{
		j = 0;
		while (j < t->x)
		{
			t->in[(i * t->x) + j] = str[start + (i * 5) + j];
			j++;
		}
		i++;
	}
}

int			ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int			getStart(t_cub *lst)
{
	int		tmp;
	int		start;
	int		i;

	tmp = lst[0].x_r;
	start = 0;
	i = 1;
	while (i < 4)
	{
		if (lst[i].x_r < tmp)
		{
			start = i;
			tmp =lst[i].x_r;
		}
		i++;
	}
	if (start == 0)
		return (lst[start].posi);
	return (lst[start].posi - (lst[start].y_r * 5));
}

int			backVerif(t_sysCub *sysCub, int pos, int dir, char *str)
{
	int		j;
	int		i;
	int		ret;
	int		posi;

	posi = getPosi(pos, dir);
	if (str[posi] != '#')
		return (1);
	j = 0;
	ret = -1;
	while (j <= sysCub->cur)
	{
		if (sysCub->lst[j].posi == posi)
			ret = j;
		j++;
	}
	if (ret < 0)
	{
		sysCub->cur++;
		ret = sysCub->cur;
		sysCub->lst[ret].posi = posi;
		if (dir == 0)
		{
			sysCub->lst[ret].x_r = sysCub->lst[ret - 1].x_r + 1;
			sysCub->lst[ret].y_r = sysCub->lst[ret - 1].y_r;
			sysCub->nbVerif[0]++;
		}
		else if (dir == 1)
		{
			sysCub->lst[ret].x_r = sysCub->lst[ret - 1].x_r;
			sysCub->lst[ret].y_r = sysCub->lst[ret - 1].y_r + 1;
			sysCub->nbVerif[1]++;
		}
		else if (dir == 2)
		{
			sysCub->lst[ret].x_r = sysCub->lst[ret - 1].x_r - 1;
			sysCub->lst[ret].y_r = sysCub->lst[ret - 1].y_r;
			sysCub->nbVerif[2]++;
		}
		else
			return (1);
	}
	if (sysCub->cur == 3)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (sysCub->lst[ret].verif[i] == FALSE)
		{
			sysCub->lst[ret].verif[i] = TRUE;
			if (!backVerif(sysCub, posi, i, str))
				return (0);
		}
		i++;
	}
	return (1);
}

int			getPosi(int pos, int dir)
{
	int		posi;

	if (dir == 0)
		posi = pos + 1;
	else if (dir == 1)
		posi = pos + 5;
	else if (dir == 2)
		posi = pos - 1;
	else
		posi = pos - 5;
	return (posi);
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

