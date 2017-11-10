/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teams.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 06:12:13 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 06:12:14 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static BOOL			in_team_history(int team_id, int *teams)
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

int					count_alive_teams(t_lemipc *lemipc)
{
	int		i;
	int		teams[TEAM_SIZE];
	int		player_team;
	int		team_count;

	i = 0;
	player_team = 0;
	team_count = 0;
	fill_zero((int*)&teams, TEAM_SIZE);
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive)
		{
			player_team = lemipc->players[i].team_id;
			if (!in_team_history(player_team, (int*)&teams))
				teams[team_count++] = player_team;
		}
		i++;
	}
	return (team_count);
}
