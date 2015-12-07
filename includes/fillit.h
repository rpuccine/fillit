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
# define FILLIT_h

# include "libft.h"

# define BUFF_SIZE 1023
# define TRUE 1
# define FALSE 0

typedef unsigned char	t_ch;

typedef struct			s_sysCub
{
	int					cur;
	t_cub[4]			lst;
}						t_tetri;

typedef struct			s_cub
{
	int					posi;
	int					verif_r;
	int					verif_d;
	int					verif_l;
	int					verif_u;
}						t_cub;

typedef struct			s_tetri
{
	int					x;
	int					y;
	unsigned char		**in;
}						t_tetri;

typedef struct			s_sys
{
	unsigned char		nb_tetri;
	t_tetri				*lst_tetri;
	unsigned char		**map;
}						t_sys;

/*
** parsing.c
*/
int						parse(t_sys *sys, int argc, char **argv);
int						fillMap(t_sys *sys, char *str, int len);
int						getNbTetri(int len);

/*
** display.c
*/
void					error();

#endif
