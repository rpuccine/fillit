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
	t_square sqr;
	t_square sqr_bu;
	sqr.x = 4;
	sqr.x = 4;
	sqr.size = 16;
	sqr_bu.x = 4;
	sqr_bu.x = 4;
	sqr_bu.size = 16;

	if (parse(&sys, argc, argv))
	{
		error();
		return (0);
	}
	//print_all_piece(&sys);
	init_map(&sys);
	do_recursion(&sys, &sqr);
	sqr_bu.x = sqr.x;
	sqr_bu.y = sqr.y;
	sqr_bu.size = sqr.size;

	print_map(&sys);

	return 0;
}
