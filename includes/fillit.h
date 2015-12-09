/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 18:49:37 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/06 22:17:55 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define BUFF_SIZE 1023
# define TRUE 1
# define FALSE 0
# define MAP_BASE_SIZE 21
# define RET 0
# define TMP 1

typedef unsigned char	t_ch;
//typedef unsigned char	**t_map;

typedef struct			s_cub
{
	int					x_r;
	int					y_r;
	int					posi;
	t_ch				verif[4];
}						t_cub;

typedef struct			s_sys_cub
{
	int					cur;
	t_ch				nb_verif[3];
	t_cub				lst[4];
}						t_sys_cub;


typedef struct			s_tetri
{
	int					x;
	int					y;
	unsigned char		*in;
}						t_tetri;

typedef struct			s_sys
{
	int					nb_tetri;
	int					area;
	int					min_sqr;
	t_tetri				*lst_tetri;
	t_ch				**map;

}						t_sys;

typedef struct			s_square
{
    int size;
    int x;
    int y;
}						t_square;

/*
** parsing.c
*/
int						parse(t_sys *sys, int argc, char **argv);
int						fill_map(t_sys *sys, char *str, int len);
int						set_tetri(t_sys *sys, char *str, int cur);
void					build_tetri(t_sys *sys, t_sys_cub *sys_cub, char *str, int cur);
int						ft_max(int a, int b);
int						get_start(t_cub *lst);
int						back_verif(t_sys_cub *sys_cub, int pos, int dir, char *str);
void					init_cub_data(t_sys_cub *sys_cub, int dir, int pos_prev, int *i_cur);
int						get_cub_index_by_posi(t_sys_cub *sys_cub, int posi);
int						get_cur_posi_by_dir(int pos, int dir);
int						verif_char(char *file);
int						get_nb_tetri(int len);

/*
** display.c
*/
void					error();
void					print_all_piece(t_sys *sys);
void					print_piece(t_tetri *t);

/*
** solve.c
*/

void    				place(unsigned char **map, t_tetri *piece, int x, int y);
int   					do_recursion(t_sys *sys, t_square *sqr);

/*
** map.c
*/
void 					init_map(t_sys *sys);
void 					print_map(t_sys *sys);
void   					set_min_sqr(t_sys *sys);

#endif
