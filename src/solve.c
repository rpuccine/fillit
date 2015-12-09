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

int     is_placable(unsigned char **map, t_tetri *piece, int x, int y)
{
  int   i;
  int   j;

  i = 0;
  while (i < piece->y)
  {
    j = 0;
    while(j < piece->x)
    {
      if (map[y + i][x + j] != '.'  && piece->in[i * piece->x + j] != '.')
        return (-1);
      j++;
    }
    i++;
  }
  return (1);
}

void    place(unsigned char **map, t_tetri *piece, int x, int y)
{
  int   i;
  int   j;

  i = 0;
  while (i < piece->y)
  {
    j = 0;
    while(j < piece->x)
    {
      if (piece->in[i * piece->x + j] != '.')
        map[y + i][x + j] = piece->in[i * piece->x + j];
      j++;
    }
    i++;
  }
}

// int   solve(t_map map, t_square *sqr, t_tetri *piece)
// {
//   int i;
//   int j;
//   // t_square  ret_sqr[2];
//
//   // ret_sqr[RET] = -1;
//   //ret_sqr[TMP] = -1;
//   i = -1;
//   while (++i < sqr->y + 1) {
//     j = -1;
//     while (++j < sqr->x + 1) {
//       if (is_placable(sys->map, piece, j, i) == 1)
//       {
//         if (ret_sqr[X] == -1)
//         {
//           if (j <= sqr->x - piece->x) {
//             ret_sqr[TMP].x = sqr->x;
//             /* code */
//           }
//
//         }
//         place(sys->map, piece, j, i);
//         return (1);
//       }
//     }
//   }
//   return (-1);
// }

int   solve(t_map map, t_square *sqr, t_tetri *piece)
{
  int i;
  int j;

  i = -1;
  while (++i < sqr->y + 1) {
    j = -1;
    while (++j < sqr->x + 1) {
      if (is_placable(map, piece, j, i) == 1)
      {
        place(map, piece, j, i);
        return (1);
      }
    }
  }
  return (-1);
}

int   do_recursion(t_sys *sys, t_square *sqr)
{
  int i;
  i = 0;
  while (i < sys->nb_tetri)
  {
    if (solve(sys->map, sqr, sys->lst_tetri + i) == -1)
    {
      sqr->x++;
      sqr->y++;
      sqr->size  = sqr->x * sqr->y;
      init_map(sys);
      do_recursion(sys, sqr);
    }
    i++;
  }
  return (1);
}
