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
#define PLAYER_RADIUS t_player *player, t_target *targets, int len, t_lemipc

t_player		*find_player_by_radius(int radius, PLAYER_RADIUS *lemipc)
{
	int	x;
	int y;
	int i;

	i = 0;
	while (i < len)
	{
		x = player->x_position - targets[i].x_position;
		y = player->y_position - targets[i].y_position;
		if (x < 0)
			x = -x;
		if (y < 0)
			y = -y;
		if (x <= radius && y <= radius)
			return (find_player_by_id(targets[i].id, lemipc));
		i++;
	}
	return (NULL);
}

#define PLAYERS_RADIUS_1 int radius, t_player *player, t_target
#define PLAYERS_RADIUS_2 t_player *players, int len, t_lemipc

int				find_players_by_radius(PLAYERS_RADIUS_1 *pos_targets, \
	PLAYERS_RADIUS_2 *lemipc)
{
	int	x;
	int y;
	int i;
	int players_count;

	i = 0;
	players_count = 0;
	while (i < len)
	{
		x = player->x_position - pos_targets[i].x_position;
		y = player->y_position - pos_targets[i].y_position;
		if (x < 0)
			x = -x;
		if (y < 0)
			y = -y;
		if (x <= radius && y <= radius)
			players[players_count++] = \
			*find_player_by_id(pos_targets[i].id, lemipc);
		i++;
	}
	return (players_count);
}

int				count_players_around(t_player *players)
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

int				count_ennemies_around(t_player *players, t_player *player)
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

#define F1 int count_mates_around(t_player *players, t_player *player)
#define F2 { int i; int len; i = 0; len = 0;
#define F3 while (i < MAX_POSSIBLE_PLAYERS_AROUND) {
#define F4 if (players[i].id != 0 && players[i].team_id == player->team_id)
#define F5 len++; i++; } return (len); }
#define FUNC F1 F2 F3 F4 F5

FUNC;

#define PLAYERS_AROUND t_player *players, t_player *player, t_lemipc

void			find_players_around(PLAYERS_AROUND *lemipc, int radius)
{
	t_target	targets[PLAYERS_SIZE];
	int			possible_target;

	fill_zero_finder((t_player*)players, MAX_POSSIBLE_PLAYERS_AROUND);
	if ((possible_target = \
		get_all_possible_players(player, (t_target*)&targets, lemipc)) > 0)
	{
		find_players_by_radius(radius, player, (t_target*)&targets, players, \
		possible_target, lemipc);
	}
}
