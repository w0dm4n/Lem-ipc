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
		players[i++].id = 0;
}

int		count_enemies_beside(t_player *players_beside, t_player *player)
{
	int		i;
	int		count_players_beside;

	// check team to avoid 1v1v1 and dying..
	i = 0;
	count_players_beside = 0;
	while (i < MAX_POSSIBLE_PLAYERS_BESIDE)
	{
		if (players_beside[i].id != 0 && players_beside[i].team_id != player->team_id)
			count_players_beside++;
		i++;
	}
	return (count_players_beside);
}

void		define_behavior(t_player *player, t_player *players, t_lemipc *lemipc)
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

void		ia_actions_handler(t_player *player, t_lemipc *lemipc)
{
	t_player	players_beside[MAX_POSSIBLE_PLAYERS_AROUND];
	t_player	players_around[MAX_POSSIBLE_PLAYERS_AROUND];

	find_players_around((t_player*)&players_beside, player, lemipc, 1);
	find_players_around((t_player*)&players_around, player, lemipc, 8);
	define_behavior(player, (t_player*)&players_around, lemipc);
	if (count_enemies_beside((t_player*)&players_beside, player) >= MAX_ENEMY_BEFORE_DEATH)
		die(player, lemipc);
}
