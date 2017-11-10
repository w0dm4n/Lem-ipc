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
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive && lemipc->players[i].id == id)
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

t_player			*get_first_alive_player(t_lemipc *lemipc)
{
	int		i;

	i = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive && lemipc->players[i].id > 0)
			return (&lemipc->players[i]);
		i++;
	}
	return (NULL);
}

int					get_random_x(int current_x)
{
	BOOL value;

	value = get_random(2);
	if (value == 1)
		return (current_x - 1);
	else
		return (current_x + 1);
}

int					get_random_y(int current_y)
{
	BOOL value;

	value = get_random(2);
	if (value == 1)
		return (current_y - 1);
	else
		return (current_y + 1);
}

void				set_pos(int x, int y, t_player *player, t_lemipc *lemipc)
{
	t_player		*on_cell;

	if ((on_cell = get_player_on_cell(lemipc, x, y)) == NULL)
	{
		reset_map_pos(lemipc, player);
		player->x_position = x;
		player->y_position = y;
		update_map_pos(lemipc, player);
	}
	else if (on_cell->team_id == player->team_id)
	{
		BOOL value = get_random(2);
		if (value == 1)
			set_pos(get_random_x(x), y, player, lemipc);
		else
			set_pos(x, get_random_y(y), player, lemipc);
	}
}

t_player			*add_new_player(int team_id, t_lemipc *lemipc)
{
	int			player_id;
	t_player	*player;
	sem_t		*sem;

	sem = get_semaphore(SEMAPHORE_NAME);
	player_id = lemipc->players_length++ + 1;
	player = NULL;
	if (team_id > 0 && (player = get_free_player(lemipc)) != NULL &&
	lemipc->players_length < (FORNORMMAPSIZE * 2))
	{
		lock(sem);
		player->id = player_id;
		player->team_id = team_id;
		player->alive = TRUE;
		if (!set_spawn_position(lemipc, player))
		{
			unlock(sem);
			return (NULL);
		}
		update_map_pos(lemipc, player);
		unlock(sem);
		close_semaphore(sem);
		return (player);
	}
	else
	{
		close_semaphore(sem);
		return (NULL);
	}
}
