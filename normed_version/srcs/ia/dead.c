/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:01:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/10 17:01:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

BOOL		team_already_set(int *teams, int team_id)
{
	int		i;

	i = 0;
	while (i < TEAM_SIZE)
	{
		if (teams[i] == team_id)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void		player_dead(t_player *players, t_player *player, t_lemipc *lemipc)
{
	int		teams[TEAM_SIZE];
	int		i;
	int		teams_count;

	fill_zero((int*)&teams, TEAM_SIZE);
	i = 0;
	teams_count = 0;
	while (i < MAX_POSSIBLE_PLAYERS_AROUND)
	{
		if (players[i].alive \
			&& players[i].team_id != player->team_id)
		{
			if (!team_already_set((int*)&teams, players[i].team_id))
				teams[teams_count++] = players[i].team_id;
			else
			{
				die(player, lemipc);
				break ;
			}
		}
		i++;
	}
}
