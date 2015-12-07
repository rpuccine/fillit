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

typedef struct			s_cub
{
	int					x_r;
	int					y_r;
	int					posi;
	t_ch[4]				verif;
}						t_cub;

typedef struct			s_sysCub
{
	int					cur;
	t_ch[3]				nbVerif;
	t_cub[4]			lst;
}						t_sysCub;

typedef struct			s_tetri
{
	int					x;
	int					y;
	unsigned char		*in;
}						t_tetri;

typedef struct			s_sys
{
	int					nb_tetri;
	t_tetri				*lst_tetri;
	unsigned char		**map;
}						t_sys;

/*
** parsing.c
*/
int						parse(t_sys *sys, int argc, char **argv);
int						fillMap(t_sys *sys, char *str, int len);
int						setTetri(t_sys *sys, char *str, int cur);
void					buildTetri(t_sys *sys, t_sysCub *sysCub, char *str, int cur);
int						ft_max(int a, int b);
int						getStart(t_Cub *lst);
int						backVerif(t_sysCub *sysCub, int pos, int dir);
int						getPosi(int pos, int dir);
int						verifChar(char *file);
int						getNbTetri(int len);

/*
** display.c
*/
void					error();
void					printAllPiece(t_sys *sys);
void					printPiece(t_tetri *t);

#endif
