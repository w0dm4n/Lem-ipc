/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_actions_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:03:03 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 10:03:09 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_player		*enemy_around(t_player *player, t_lemipc *lemipc)
{
	if (lemipc->map[player->x_position - 1][player->y_position] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position - 1, player->y_position));
	else if (lemipc->map[player->x_position - 1][player->y_position - 1] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position - 1, player->y_position - 1));
	else if (lemipc->map[player->x_position - 1][player->y_position + 1] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position - 1, player->y_position + 1));
	else if (lemipc->map[player->x_position + 1][player->y_position] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position + 1, player->y_position));
	else if (lemipc->map[player->x_position + 1][player->y_position - 1] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position + 1, player->y_position - 1));
	else if (lemipc->map[player->x_position + 1][player->y_position + 1] != FREE_CELL)
		return (get_player_on_cell(lemipc, player->x_position + 1, player->y_position + 1));
	return (NULL);
}

void		ia_actions_handler(t_player *player, t_lemipc *lemipc)
{
	t_player	*target;
	t_player	*around;

	if ((around = enemy_around(player, lemipc)) != NULL && \
		around->team_id != player->team_id)
		return ;
	target = find_nearest_enemy(player, lemipc);
	if (target)
	{
		move_to_enemy(player, target, lemipc);
	}
}
