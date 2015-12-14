/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_specific.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 16:06:35 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/14 16:06:39 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				solve_first(t_sys *sys)
{
	int			i;

	i = 0;
	while (i < sys->nb_tetri)
	{
		place_piece_first(sys, sys->lst_tetri + i);
		i++;
	}
	if (verif_soluce(sys))
		return (1);
	sys->size_first = sys->size_map;
	sys->size_map = 0;
	free(sys->map);
	sys->map = malloc_map();
	sys->nb_placed = 0;
	return (0);
}

void			place_piece_first(t_sys *sys, t_tetri *t)
{
	int			i;
	int			j;
	t_square	ret;
	t_square	tmp;

	ret.size = -1;
	i = -1;
	while (++i < sys->size_map + 1)
	{
		j = -1;
		while (++j < sys->size_map + 1)
		{
			tmp.x = j;
			tmp.y = i;
			tmp.size = -1;
			if (is_placable(sys, t, &tmp)
				&& (ret.size == -1 || tmp.size < ret.size))
			{
				ret.x = tmp.x;
				ret.y = tmp.y;
				ret.size = tmp.size;
			}
		}
	}
	place_in_map(sys, t, &ret);
}

int				place_piece_recurse(t_sys *sys, t_tetri *t)
{
	int			i;
	int			j;

	i = 0;
	while (i < sys->size_first)
	{
		j = 0;
		while (j < sys->size_first)
		{
			if (place_sequence_recurse(sys, t, j, i))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				place_sequence_recurse(t_sys *sys, t_tetri *t, int x, int y)
{
	t_square		tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.size = -1;
	if (tmp.x + t->x > sys->size_solved || tmp.y + t->y > sys->size_solved)
		return (0);
	if (is_placable(sys, t, &tmp) == TRUE)
	{
		place_in_map(sys, t, &tmp);
		if (sys->nb_placed == sys->nb_tetri)
		{
			if (verif_soluce(sys))
				return (1);
			unplace_piece(sys, t);
			return (0);
		}
		if (place_piece_recurse(sys, t + 1))
			return (1);
		unplace_piece(sys, t);
	}
	return (0);
}
