/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:03:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 23:03:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void		fill_zero_map(int *map_y)
{
	int		y;

	y = 0;
	while (y < MAP_SIZE)
		map_y[y++] = FREE_CELL;
}

void			init_map(t_lemipc *lemipc)
{
	int		x;

	x = 0;
	while (x < MAP_SIZE)
		fill_zero_map((int*)&lemipc->map[x++]);
}
