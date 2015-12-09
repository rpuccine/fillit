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

int     solve(t_ch **map, t_tetri *lst, int nb_tetri, t_sys *sys)
{
  int   i;

  i = 0;
  while (i < nb_tetri)
  {
    place_piece();
    if (nb_tetri == 1)
    {
      if (size_sqr_cur_soluce == min_sqr)
        return (eureka)
      else
      {
        if (cur_soluce is first_soluce)
          set sys_soluce with cur_soluce
        else
          if (size_sqr_cur_soluce < size_sqr_sys_soluce)
            replace sys_soluce with cur_soluce
      }
      maybe unplace_piece();
      return anyway;
    }
    if (solve()->nextlevel == eureka)
      return (eureka)
    else
      maybe unplace_piece();
    i++;
  }
}

int     is_placable(t_ch **map, t_tetri *piece, int x, int y)
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

void    place(t_ch **map, t_tetri *piece, int x, int y)
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

 /*int   solve(t_map map, t_square *sqr, t_tetri *piece)
 {
   int i;
   int j;
   // t_square  ret_sqr[2];

   // ret_sqr[RET] = -1;
   //ret_sqr[TMP] = -1;
   i = -1;
   while (++i < sqr->y + 1) {
     j = -1;
    while (++j < sqr->x + 1) {
      if (is_placable(sys->map, piece, j, i) == 1)
       {
         if (ret_sqr[X] == -1)
         {
           if (j <= sqr->x - piece->x) {
             ret_sqr[TMP].x = sqr->x;
              code 
           }

         }
         place(sys->map, piece, j, i);
         return (1);
       }
     }
   }
   return (-1);
 }*/
