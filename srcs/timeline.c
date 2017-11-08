/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:10:17 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 22:37:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "lists.h"

void		set_player_turn(t_player *player, t_timeline *timeline)
{
	timeline->current_player_id = player->id;
	timeline->history_players[timeline->history_count++] = player->id;
}

void		default_timeline(t_timeline *timeline, t_lemipc *lemipc)
{
	int			i;
	t_player	*player;

	i = 0;
	player = NULL;
	if (timeline->current_player_id == 0)
	{
		if ((player = get_first_alive_player(lemipc)) != NULL)
			set_player_turn(player, timeline);
	}
}

BOOL		my_turn(t_player *player, t_lemipc *lemipc, t_timeline *timeline, sem_t *sem)
{
	t_player	*action_player;

	action_player = NULL;
	if (timeline->current_player_id == player->id)
	{
		lock(sem);
		if (count_alive_teams(lemipc) > 1)
			timeline->round++;
		return (TRUE);
	}
	else
	{
		action_player = find_player_by_id(timeline->current_player_id, lemipc);
		if (action_player == NULL || action_player->alive == FALSE)
			get_next_player_turn(timeline, lemipc);
	}
	default_timeline(timeline, lemipc);
	return (FALSE);
}

BOOL		in_timeline_history(t_player *player, t_timeline *timeline)
{
	int i;

	i = 0;
	while (i < HISTORY)
	{
		if (timeline->history_players[i] == player->id)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

BOOL		reset_history_timeline(t_timeline *timeline, t_lemipc *lemipc)
{
	int			i;
	t_player	*player;

	i = 0;
	if ((player = get_first_alive_player(lemipc)) != NULL)
	{
		while (i < HISTORY)
			timeline->history_players[i++] = 0;
		timeline->history_count = 0;
		set_player_turn(player, timeline);
		return (TRUE);
	}
	else
		return (FALSE);
}

BOOL		get_next_player_turn(t_timeline *timeline, t_lemipc *lemipc)
{
	int	i;

	if (timeline->history_count > HISTORY)
		return (reset_history_timeline(timeline, lemipc));
	i = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive &&
			!in_timeline_history(&lemipc->players[i], timeline))
		{
			set_player_turn(&lemipc->players[i], timeline);
			return (TRUE);
		}
		i++;
	}
	return (reset_history_timeline(timeline, lemipc));
}

BOOL		end_turn(t_player *player, t_timeline *timeline, t_lemipc *lemipc, sem_t *sem)
{
	unlock(sem);
	if (count_alive_teams(lemipc) > 1)
		return (get_next_player_turn(timeline, lemipc));
	else if (timeline->round == 0)
	{
		printf("There is only one team... i'm waiting for other players "
		"on other teams to have some fun with :(\n");
		 return (TRUE);
	}
	return (FALSE);
}

void		check_fight_end(t_lemipc *lemipc)
{
	if (count_alive_teams(lemipc) <= 1 && lemipc->timeline.round > 0)
		end_lemipc(lemipc);
}

void		start_actions_loop(t_player *player, t_lemipc *lemipc)
{
	t_timeline	*timeline;
	sem_t		*sem;

	sem = get_semaphore(SEMAPHORE_NAME);
	timeline = &lemipc->timeline;
	while (player->alive && !lemipc->game_over)
	{
		default_timeline(timeline, lemipc);
		if (my_turn(player, lemipc, timeline, sem))
		{
			printf("It's my turn to play ! (player id: %d, team: %d), team alive count: %d\n",
			player->id, player->team_id, count_alive_teams(lemipc));
			ia_actions_handler(player, lemipc);
			if (!end_turn(player, timeline, lemipc, sem))
				end_lemipc(lemipc);
			check_fight_end(lemipc);
		}
		else
			printf("It's not my turn to play !\n");
		usleep(ACTIONSLOOPTIME * 1000);
	}
	close_semaphore(sem);
	if (!g_global.ended_the_game)
		print_result(lemipc);
}

void		timeline(t_player *player, t_lemipc *lemipc)
{
	if (!player)
	{
		printf("Map is full cant have some new players !\n");
		return ;
	}
	g_global.player = player;
	g_global.lemipc = lemipc;
	start_actions_loop(player, lemipc);
}

void		init_timeline(t_lemipc *lemipc)
{
	int i;

	i = 0;
	lemipc->timeline.round = 0;
	lemipc->timeline.current_player_id = 0;
	lemipc->timeline.history_count = 0;
	while (i < HISTORY)
		lemipc->timeline.history_players[i++] = 0;
}
