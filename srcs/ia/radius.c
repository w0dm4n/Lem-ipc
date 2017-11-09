/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radius.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:39:38 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/09 17:39:44 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	find_by_radius(int radius, t_player *player, t_target *possible_targets, \
	t_player *players, int len, t_lemipc *lemipc)
{
	int	x;
	int y;
	int i;
	int players_count;

	i = 0;
	players_count = 0;
	while (i < len)
	{
		x = player->x_position - possible_targets[i].x_position;
		y = player->y_position - possible_targets[i].y_position;
		if (x < 0)
			x = -x;
		if (y < 0)
			y = -y;
		if (x < radius && y < radius)
			players[players_count++] = *find_player_by_id(possible_targets[i].id, lemipc);
		i++;
	}
	return (players_count);
}

int			count_players_around(t_player *players)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < MAX_POSSIBLE_PLAYERS_AROUND)
	{
		if (players[i].id != 0)
			len++;
		i++;
	}
	return (len);
}

int			count_ennemies_around(t_player *players, t_player *player)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < MAX_POSSIBLE_PLAYERS_AROUND)
	{
		if (players[i].id != 0 && players[i].team_id != player->team_id)
			len++;
		i++;
	}
	return (len);
}

int			count_mates_around(t_player *players, t_player *player)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < MAX_POSSIBLE_PLAYERS_AROUND)
	{
		if (players[i].id != 0 && players[i].team_id == player->team_id)
			len++;
		i++;
	}
	return (len);
}

void		find_players_around(t_player *players, t_player *player, t_lemipc *lemipc, int radius)
{
	t_target	targets[PLAYERS_SIZE];
	int			possible_target;

	fill_zero_finder((t_player*)players, MAX_POSSIBLE_PLAYERS_AROUND);
	if ((possible_target = get_all_possible_players(player, (t_target*)&targets, lemipc)) > 0)
		find_by_radius(radius, player, (t_target*)&targets, players, possible_target, lemipc);
}
