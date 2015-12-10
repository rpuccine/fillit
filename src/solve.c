/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravenel <mravenel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:13:37 by mravenel          #+#    #+#             */
/*   Updated: 2015/12/09 15:13:38 by mravenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int     solve_first(t_sys *sys)
{
  int   i;

  i = 0;
  while (i < sys->nb_tetri)
  {
    place_piece(sys, sys->lst_tetri + i);
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

int     verif_soluce(t_sys *sys)
{
  int   i;
  int   j;

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

int    place_piece_recurse(t_sys *sys, t_tetri *t)
{
  int       i;
  int       j;
  t_square  tmp;

  i = 0;
  while (i < sys->size_first)
  {
    j = 0;
    while (j < sys->size_first)
    {
      tmp.x = j;
      tmp.y = i;
      tmp.size = -1;
      if (is_placable_recurse(sys, t, &tmp) == TRUE)
      {
        place_in_map(sys, t, &tmp);
        //debug_print_map(sys);
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
      j++;
    }
    i++;
  }
  return (0);
}

int     is_placable_recurse(t_sys *sys, t_tetri *t, t_square *sqr)
{
  int   i;
  int   j;
  int   test_size;
  t_ch  **map;

  map = sys->map;
  i = 0;
  while (i < t->y)
  {
    j = 0;
    while(j < t->x)
    {
      if (map[sqr->y + i][sqr->x + j] != '.'  && t->in[i * t->x + j] != '.')
        return (FALSE);
      j++;
    }
    i++;
  }
  if (sqr->x + t->x > sys->size_solved || sqr->y + t->y > sys->size_solved)
    return (FALSE);
  if ((test_size = ft_max(sqr->x + t->x, sqr->y + t->y)) > sys->size_map)
    sqr->size = test_size;
  else
    sqr->size = sys->size_map;
  return (TRUE);
}

void    place_piece(t_sys *sys, t_tetri *t)
{
  int       i;
  int       j;
  t_square  ret;
  t_square  tmp;

  ret.size = -1;
  i = 0;
  while (i < sys->size_map + 1)
  {
    j = 0;
    while (j < sys->size_map + 1)
    {
      tmp.x = j;
      tmp.y = i;
      tmp.size = -1;
      if (is_placable(sys, t, &tmp) == TRUE)
      {
        if (ret.size == -1 || tmp.size < ret.size)
        {
          ret.x = tmp.x;
          ret.y = tmp.y;
          ret.size = tmp.size;
        }
      }
      j++;
    }
    i++;
  }
  place_in_map(sys, t, &ret);
  //debug_print_map(sys);
}


int     is_placable(t_sys *sys, t_tetri *t, t_square *sqr)
{
  int   i;
  int   j;
  int   test_size;
  t_ch  **map;

  map = sys->map;
  i = 0;
  while (i < t->y)
  {
    j = 0;
    while(j < t->x)
    {
      if (map[sqr->y + i][sqr->x + j] != '.'  && t->in[i * t->x + j] != '.')
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

void    place_in_map(t_sys *sys, t_tetri *piece, t_square *sqr)
{
  int   i;
  int   j;
  t_ch  **map;

  piece->is_placed = TRUE;
  piece->placed_x = sqr->x;
  piece->placed_y = sqr->y;
  map = sys->map;
  sys->nb_placed++;
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
    while(j < piece->x)
    {
      if (piece->in[i * piece->x + j] != '.')
        map[sqr->y + i][sqr->x + j] = piece->in[i * piece->x + j];
      j++;
    }
    i++;
  }
}

void  unplace_piece(t_sys *sys, t_tetri *t)
{
  int   i;
  int   j;
  t_ch  **map;

  map = sys->map;
  sys->nb_placed--;
  i = 0;
  while (i < t->y)
  {
    j = 0;
    while(j < t->x)
    {
      if (t->in[i * t->x + j] != '.')
        map[t->placed_y + i][t->placed_x + j] = '.';
      j++;
    }
    i++;
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









