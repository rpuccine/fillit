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
	write(1, "error", 5);
	write(1, "\n", 1);
}

void	print_map(t_ch **map, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		write(1, (const char*)map[i], size);
		write(1, "\n", 1);
	}
}
