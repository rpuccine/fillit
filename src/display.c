/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 19:18:04 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/06 20:04:18 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error(void)
{
	ft_putendl("error");
}

void	printAllPiece(t_sys *sys)
{
	int	i;

	printf("Nb piece : %d\n", sys->nb_tetri);
	i = 0;
	while (i < sys->nb_tetri)
	{
		printPiece(sys->lst_tetri + i);
		i++;
	}
}

void	printPiece(t_tetri *t)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	printf("\n**** Piece x=%d y=%d *****\n", t->x, t->y);

	while (i < t->y)
	{
		j = 0;
		while (j < t->x)
		{
			printf("%c",t->in[x]);
			x++;
			j++;
		}
		printf("\n");
		i++;
	}
	printf("****** End Piece ********\n");
}