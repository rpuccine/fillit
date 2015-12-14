/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravenel <mravenel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:13:37 by mravenel          #+#    #+#             */
/*   Updated: 2015/12/14 16:22:56 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			is_placable(t_sys *sys, t_tetri *t, t_square *sqr)
{
	int		i;
	int		j;
	int		test_size;
	t_ch	**map;

	map = sys->map;
	i = 0;
	while (i < t->y)
	{
		j = 0;
		while (j < t->x)
		{
			if (map[sqr->y + i][sqr->x + j] != '.'
				&& t->in[i * t->x + j] != '.')
				return (FALSE);
			j++;
		}
		i++;
	}
	if ((test_size = ft_max(sqr->x + t->x, sqr->y + t->y)) > sys->size_map)
		sqr->size = test_size;
	else
		sqr->size = sys->size_map;
	return (TRUE);
}

void		place_in_map(t_sys *sys, t_tetri *piece, t_square *sqr)
{
	int		i;
	int		j;
	t_ch	**map;

	set_placed_piece_data(sys, piece, sqr);
	map = sys->map;
	if (sqr->size > sys->size_map)
	{
		piece->old_size = sys->size_map;
		sys->size_map = sqr->size;
	}
	else
		piece->old_size = -1;
	i = 0;
	while (i < piece->y)
	{
		j = 0;
		while (j < piece->x)
		{
			if (piece->in[i * piece->x + j] != '.')
				map[sqr->y + i][sqr->x + j] = piece->in[i * piece->x + j];
			j++;
		}
		i++;
	}
}

void		set_placed_piece_data(t_sys *sys, t_tetri *piece, t_square *sqr)
{
	piece->is_placed = TRUE;
	piece->placed_x = sqr->x;
	piece->placed_y = sqr->y;
	sys->nb_placed++;
}

void		unplace_piece(t_sys *sys, t_tetri *t)
{
	int		i;
	int		j;
	t_ch	**map;

	map = sys->map;
	sys->nb_placed--;
	i = -1;
	while (++i < t->y)
	{
		j = -1;
		while (++j < t->x)
		{
			if (t->in[i * t->x + j] != '.')
				map[t->placed_y + i][t->placed_x + j] = '.';
		}
	}
	if (t->old_size != -1)
	{
		sys->size_map = t->old_size;
		t->old_size = -1;
	}
	t->is_placed = FALSE;
	t->placed_x = -1;
	t->placed_y = -1;
}

int			verif_soluce(t_sys *sys)
{
	int		i;
	int		j;

	if (sys->solved_map == NULL || sys->size_map < sys->size_solved)
	{
		free(sys->solved_map);
		sys->solved_map = malloc_map();
		i = 0;
		while (i < sys->size_map)
		{
			j = 0;
			while (j < sys->size_map)
			{
				sys->solved_map[i][j] = sys->map[i][j];
				j++;
			}
			i++;
		}
		sys->size_solved = sys->size_map;
		if (sys->size_map == sys->min_sqr)
			return (1);
	}
	return (0);
}
