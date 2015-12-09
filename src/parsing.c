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

	ft_bzero((void*)&sys_cub, sizeof(t_sys_cub));
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			j = 0;
			sys_cub.lst[0].posi = i;
			while (j < 4)
			{
				sys_cub.lst[0].verif[j] = TRUE;
				if (!back_verif(&sys_cub, i, j, str))
				{
					build_tetri(sys, &sys_cub, str, cur);
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

void		build_tetri(t_sys *sys, t_sys_cub *sys_cub, char *str, int cur)
{
	int		start;
	int		i;
	int		j;
	t_tetri	*t;

	t = sys->lst_tetri + cur;
	t->x = ft_max(sys_cub->nb_verif[0], sys_cub->nb_verif[2]) + 1;
	t->y = sys_cub->nb_verif[1] + 1;
	start = get_start(sys_cub->lst);
	printf("Start = %d\n", start);
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

int			get_start(t_cub *lst)
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

int			back_verif(t_sys_cub *sys_cub, int pos_prev, int dir, char *str)
{
	int		i;
	int		i_cur;
	int		pos_cur;

	pos_cur = get_cur_posi_by_dir(pos_prev, dir);
	if (str[pos_cur] != '#')
		return (1);
	sys_cub->nb_verif[dir]++;
	if ((i_cur = get_cub_index_by_posi(sys_cub, pos_cur)) < 0)
		init_cub_data(sys_cub, dir, pos_prev, &i_cur);
	if (sys_cub->cur == 3)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (sys_cub->lst[i_cur].verif[i] == FALSE)
		{
			sys_cub->lst[i_cur].verif[i] = TRUE;
			if (!back_verif(sys_cub, pos_cur, i, str))
				return (0);
		}
		i++;
	}
	return (1);
}

void		init_cub_data(t_sys_cub *sys_cub, int dir, int pos_prev, int *i_cur)
{
	int		i_prev;

	sys_cub->cur++;
	*i_cur = sys_cub->cur;
	sys_cub->lst[*i_cur].posi = get_cur_posi_by_dir(pos_prev, dir);
	i_prev = get_cub_index_by_posi(sys_cub, pos_prev);
	if (dir == 0)
	{
		sys_cub->lst[*i_cur].x_r = sys_cub->lst[i_prev].x_r + 1;
		sys_cub->lst[*i_cur].y_r = sys_cub->lst[i_prev].y_r;
	}
	else if (dir == 1)
	{
		sys_cub->lst[*i_cur].x_r = sys_cub->lst[i_prev].x_r;
		sys_cub->lst[*i_cur].y_r = sys_cub->lst[i_prev].y_r + 1;
	}
	else if (dir == 2)
	{
		sys_cub->lst[*i_cur].x_r = sys_cub->lst[i_prev].x_r - 1;
		sys_cub->lst[*i_cur].y_r = sys_cub->lst[i_prev].y_r;
	}
}

int			get_cub_index_by_posi(t_sys_cub *sys_cub, int posi)
{
	int		i;

	i = 0;
	while (i < sys_cub->cur)
	{
		if (sys_cub->lst[i].posi == posi)
			return (i);
		i++;
	}
	return (-1);
}

int			get_cur_posi_by_dir(int pos, int dir)
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

int			verif_char(char *file)
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

int			get_nb_tetri(int len)
{
	int nb_tetri;

	nb_tetri = len / 20;
	if (nb_tetri >= 22)
		nb_tetri--;
	return (nb_tetri);
}

