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

void			init_map(t_lemipc *lemipc)
{
	int		x;

	x = 0;
	while (x < MAP_SIZE)
		fill_zero((int*)&lemipc->map[x++], MAP_SIZE);
}
