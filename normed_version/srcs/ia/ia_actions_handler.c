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

void		fill_zero_finder(t_player *players, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		players[i].id = 0;
		players[i].x_position = 0;
		players[i].y_position = 0;
		players[i].alive = 0;
		players[i].team_id = 0;
		i++;
	}
}

#define T t_lemipc

void		define_behavior(t_player *player, t_player *players, T *lemipc)
{
	t_player	*target;
	int			enemies_around;
	int			mates_around;
	int			all_mates;

	target = NULL;
	enemies_around = count_ennemies_around(players, player);
	mates_around = count_mates_around(players, player);
	all_mates = count_mates(player, lemipc);
	if (enemies_around >= 1 && mates_around == 0 && all_mates > 0)
	{
		if ((target = find_nearest_friend(player, lemipc)) != NULL)
			move_to_target(player, target, lemipc);
	}
	else if ((mates_around + 1) > enemies_around)
	{
		if ((target = find_nearest_enemy(player, lemipc)) != NULL)
			move_to_target(player, target, lemipc);
	}
	else if ((target = find_nearest_enemy(player, lemipc)) != NULL)
		move_to_target(player, target, lemipc);
}

#define VARS (t_player*)&players_beside, player

void		ia_actions_handler(t_player *player, t_lemipc *lemipc)
{
	t_player	players_beside[MAX_POSSIBLE_PLAYERS_AROUND];
	t_player	players_around[MAX_POSSIBLE_PLAYERS_AROUND];

	find_players_around((t_player*)&players_beside, player, lemipc, 1);
	find_players_around((t_player*)&players_around, player, lemipc, 8);
	define_behavior(player, (t_player*)&players_around, lemipc);
	player_dead(VARS, lemipc);
}
