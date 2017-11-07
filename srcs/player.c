/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 05:51:05 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 05:51:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_player			*find_player_by_id(int id, t_lemipc *lemipc)
{
	int		i;

	i = 0;
	while (i < lemipc->players_length)
	{
		if (lemipc->players[i].id == id)
			return (&lemipc->players[i]);
		i++;
	}
	return (NULL);
}

static BOOL			set_spawn_position(t_lemipc *lemipc, t_player *player)
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
	}
	return (FALSE);
}

int					count_alive_players(t_lemipc *lemipc)
{
	int		i;
	int		alive_players;

	i = 0;
	alive_players = 0;
	while (i < lemipc->players_length)
	{
		if (lemipc->players[i].alive == TRUE)
			alive_players += 1;
		i++;
	}
	return (alive_players);
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

t_player			*add_new_player(int team_id, t_lemipc *lemipc)
{
	int			player_id;
	t_player	*player;
	sem_t		*sem;

	sem = get_semaphore(SEMAPHORE_NAME);
	player_id = 0;
	player = NULL;
	if (team_id > 0 && (player = get_free_player(lemipc)) != NULL)
	{
		lock(sem);
		player->id = lemipc->players_length++;
		player->team_id = team_id;
		player->alive = TRUE;
		if (!set_spawn_position(lemipc, player))
		{
			unlock(sem);
			return (NULL);
		}
		unlock(sem);
		update_pos(lemipc, player);
		return (player);
	}
	else
		return (NULL);
}
