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
	print_all_piece(&sys);
	return 0;
}
