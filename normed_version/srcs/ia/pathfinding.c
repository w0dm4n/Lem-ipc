/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:01:38 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 10:01:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			fill_zero_targets(t_target *targets)
{
	int i;

	i = 0;
	while (i < PLAYERS_SIZE)
	{
		targets[i].id = 0;
		targets[i].x_position = 0;
		targets[i].y_position = 0;
		i++;
	}
}

int				get_all_possible_players(t_player *player, t_target *targets, \
	t_lemipc *lemipc)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	fill_zero_targets(targets);
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive && lemipc->players[i].id != player->id)
		{
			targets[len].id = lemipc->players[i].id;
			targets[len].x_position = lemipc->players[i].x_position;
			targets[len].y_position = lemipc->players[i].y_position;
			len++;
		}
		i++;
	}
	return (len);
}

void			move_to_target(t_player *player, t_player *target, \
	t_lemipc *lemipc)
{
	int x;
	int y;

	x = player->x_position - target->x_position;
	y = player->y_position - target->y_position;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (x > 1 || y > 1)
	{
		if (target->y_position > player->y_position)
			set_pos(player->x_position, player->y_position + 1, player, lemipc);
		else if (target->y_position < player->y_position)
			set_pos(player->x_position, player->y_position - 1, player, lemipc);
		else
		{
			if (target->x_position > player->x_position)
				set_pos(player->x_position + 1, player->y_position, \
					player, lemipc);
			else if (target->x_position < player->x_position)
				set_pos(player->x_position - 1, player->y_position, \
					player, lemipc);
		}
	}
}
