#include "fillit.h"

void init_map(t_sys *sys)
{
  int   i;

  sys->map = malloc(sizeof(unsigned char *) * 21);
  i = -1;
  while (++i < 21)
    sys->map[i] = malloc(sizeof(unsigned char) * 21);

  i = -1;
  while (++i < 21)
    ft_memset(sys->map[i], '.', 21);
}

void print_map(t_sys *sys)
{
  int   i ;

  i = -1;
  while (++i < 21)
  {
    write(1, (const char*)sys->map[i], 21);
    ft_putendl("");
  }
}
