/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 05:23:28 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 05:23:33 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

BOOL			is_cell_free(int x, int y, t_lemipc *lemipc)
{
	if (lemipc->map[x][y] != FREE_CELL)
		return (FALSE);
	else
		return (TRUE);
}

t_player		*get_player_on_cell(t_lemipc *lemipc, int x, int y)
{
	if (x < 0 || y < 0 || x > MAP_SIZE || y > MAP_SIZE)
		return (NULL);
	if (lemipc->map[x][y] != FREE_CELL)
		return (find_player_by_id(lemipc->map[x][y], lemipc));
	return (NULL);
}

void			reset_map_pos(t_lemipc *lemipc, t_player *player)
{
	if (player->x_position >= 0 && player->y_position >= 0 && player->x_position < MAP_SIZE && player->y_position < MAP_SIZE)
		lemipc->map[player->x_position][player->y_position] = FREE_CELL;
}

void			update_map_pos(t_lemipc *lemipc, t_player *player)
{
	lemipc->map[player->x_position][player->y_position] = player->id;
}
