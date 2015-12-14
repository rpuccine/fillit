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
	if (fill_map(sys, buff, offset))
		return (1);
	return (0);
}

int			fill_map(t_sys *sys, char *str, int len)
{
	int		i;
	int		offset;

	sys->nb_tetri = get_nb_tetri(len);
	if (!(sys->lst_tetri =
		(t_tetri *)malloc(sizeof(t_tetri) * sys->nb_tetri)))
		return (1);
	offset = 0;
	i = 0;
	while (i < sys->nb_tetri)
	{
		if (verif_char(str + offset))
			return (1);
		if (set_tetri(sys, str + offset, i))
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

int			set_tetri(t_sys *sys, char *str, int cur)
{
	t_sys_cub	sys_cub;
	int			i;
	int			j;

	ft_memset((void*)&sys_cub, 0, sizeof(t_sys_cub));
	i = -1;
	while (++i < 20)
	{
		if (str[i] == '#')
		{
			sys_cub.lst[0].posi = i;
			j = -1;
			while (++j < 4)
			{
				sys_cub.lst[0].verif[j] = TRUE;
				if (!back_verif(&sys_cub, i, j, str))
				{
					build_tetri(sys, &sys_cub, str, cur);
					return (0);
				}
			}
			return (1);
		}
	}
	return (1);
}

void		build_tetri(t_sys *sys, t_sys_cub *sys_cub, char *str, int cur)
{
	int		start;
	int		i;
	int		j;
	t_tetri	*t;

	t = init_piece_data(sys, sys_cub, cur);
	start = get_start(sys_cub->lst);
	t->in = (t_ch *)malloc(sizeof(t_ch) * (t->x * t->y));
	i = 0;
	while (i < t->y)
	{
		j = 0;
		while (j < t->x)
		{
			if (str[start + (i * 5) + j] == '.')
				t->in[(i * t->x) + j] = '.';
			else
				t->in[(i * t->x) + j] = t->c;
			j++;
		}
		i++;
	}
}

t_tetri		*init_piece_data(t_sys *sys, t_sys_cub *sys_cub, int cur)
{
	t_tetri	*t;

	t = sys->lst_tetri + cur;
	t->x = ft_max(sys_cub->nb_verif[0], sys_cub->nb_verif[2]) + 1;
	t->y = sys_cub->nb_verif[1] + 1;
	t->is_placed = FALSE;
	t->placed_x = -1;
	t->placed_y = -1;
	t->c = 65 + cur;
	return (t);
}
