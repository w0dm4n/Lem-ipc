/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:43:12 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/10 15:43:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_player			*find_player_by_id(int id, t_lemipc *lemipc)
{
	int		i;

	i = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive && lemipc->players[i].id == id)
			return (&lemipc->players[i]);
		i++;
	}
	return (NULL);
}

BOOL				set_spawn_position(t_lemipc *lemipc, t_player *player)
{
	int x;
	int y;
	int	retry;

	x = 0;
	y = 0;
	retry = 0;
	while (retry < MAP_SIZE)
	{
		x = get_random((MAP_SIZE - 1));
		y = get_random((MAP_SIZE - 1));
		if (!get_player_on_cell(lemipc, x, y))
		{
			player->x_position = x;
			player->y_position = y;
			return (TRUE);
		}
		else
			retry++;
		usleep(FORNORMSPAWNPOS * 1000);
	}
	return (FALSE);
}

int					count_alive_players(t_lemipc *lemipc)
{
	int		i;
	int		alive_players;

	i = 0;
	alive_players = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive == TRUE)
			alive_players += 1;
		i++;
	}
	return (alive_players);
}

void				die(t_player *player, t_lemipc *lemipc)
{
	t_msg_buf	msg;

	if (player->alive && player->id != 0)
	{
		get_next_player_turn(&lemipc->timeline, lemipc);
		printf("Player dead (%d)\n", player->id);
		reset_map_pos(lemipc, player);
		player->id = 0;
		player->alive = FALSE;
		player->x_position = 0;
		player->y_position = 0;
		lemipc->players_length -= 1;
		if (lemipc->players_length < 0)
			lemipc->players_length = 0;
	}
}

t_player			*get_free_player(t_lemipc *lemipc)
{
	int		i;

	i = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive == FALSE)
			return (&lemipc->players[i]);
		i++;
	}
	return (NULL);
}
