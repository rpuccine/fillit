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

	i = 0;
	while (i < sys->nb_tetri)
	{
		printPiece(sys->lst_tetri + i);
		ft_putchar('\n');
		i++;
	}
}

void	printPiece(t_tetri *t)
{
	int	i;
	int	j;

	i = 0;
	while (i < t->y)
	{
		j = 0;
		while (j < t->x)
		{
			ft_putchar(t->in[i * t->x + j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}