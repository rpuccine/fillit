#include "fillit.h"

void init_map(t_sys *sys)
{
  sys->area = sys->nb_tetri * 4;
  set_min_sqr(sys);
  sys->solved_map = NULL;
  sys->size_solved = 0;
  sys->size_map = 0;
  sys->nb_placed = 0;
  sys->map = malloc_map();
}

void   set_min_sqr(t_sys *sys)
{
  int   i;

  i = 4;
  while (i < 22)
  {
    if (i * i >= sys->area)
    {
      sys->min_sqr = i;
      return ;
    }
    i++;
  }
}

t_ch  **malloc_map(void)
{
  int   i;
  t_ch  **map; 

  map = (t_ch **)malloc(sizeof(t_ch *) * 21);
  i = -1;
  while (++i < 21)
  {
    map[i] = (t_ch *)malloc(sizeof(t_ch) * 21);
    ft_memset(map[i], '.', 21);
  }
  return (map);
}