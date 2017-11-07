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

static void		fill_zero_map(int *map_y)
{
	int		y;

	y = 0;
	while (y < MAP_SIZE)
		map_y[y++] = FREE_CELL;
}

t_player		*get_player_on_cell(t_lemipc *lemipc, int x, int y)
{
	t_player	*player;

	player = NULL;
	if (lemipc->map[x][y] != FREE_CELL)
		return (find_player_by_id(lemipc->map[x][y], lemipc));
	return (player);
}

void			update_pos(t_lemipc *lemipc, t_player *player)
{
	sem_t		*sem;

	sem = get_semaphore(SEMAPHORE_NAME);
	lock(sem);
	lemipc->map[player->x_position][player->y_position] = player->id;
	printf("Map updated !\n");
	unlock(sem);
}

void			init_map(t_lemipc *lemipc)
{
	int		x;

	x = 0;
	while (x < MAP_SIZE)
		fill_zero_map((int*)&lemipc->map[x++]);
}
