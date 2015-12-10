/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 21:44:30 by rpuccine          #+#    #+#             */
/*   Updated: 2015/12/06 20:03:37 by rpuccine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	t_sys sys;

	if (parse(&sys, argc, argv))
	{
		error();
		return (0);
	}
	init_map(&sys);
	print_all_piece(&sys);
	solve_first(&sys);
	ft_putendl("");
	print_map(sys.solved_map, sys.size_solved);
	place_piece_recurse(&sys, sys.lst_tetri);
	ft_putendl("");
	print_map(sys.solved_map, sys.size_solved);

	return 0;
}
