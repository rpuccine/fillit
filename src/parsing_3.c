/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 17:19:27 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/14 17:19:29 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			verif_char(char *file)
{
	int		i;
	int		j;
	int		cub;

	i = 0;
	cub = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (file[i * 5 + j] != '.' && file[i * 5 + j] != '#')
				return (1);
			if (file[i * 5 + j] == '#')
				cub++;
			j++;
		}
		if (file[i * 5 + j] != '\n')
			return (1);
		i++;
	}
	if (cub != 4)
		return (1);
	return (0);
}

int			get_nb_tetri(int len)
{
	int nb_tetri;

	nb_tetri = len / 20;
	if (nb_tetri >= 22)
		nb_tetri--;
	return (nb_tetri);
}

int			ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void		*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)str;
	i = -1;
	while (++i < len)
		s[i] = (unsigned char)c;
	return (str);
}
