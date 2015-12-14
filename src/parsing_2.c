/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 17:19:18 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/14 17:19:20 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
			tmp = lst[i].x_r;
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
