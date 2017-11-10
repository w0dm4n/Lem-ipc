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

void		reset_timeline(t_lemipc *lemipc, sem_t *sem)
{
	lock(sem);
	reset_history_timeline(&lemipc->timeline, lemipc);
	unlock (sem);
}

void		default_timeline(t_timeline *timeline, t_lemipc *lemipc, sem_t *sem)
{
	t_player	*current;

	current = NULL;
	if (timeline->current_player_id == 0)
		reset_timeline(lemipc, sem);
}

BOOL		my_turn(t_player *player, t_lemipc *lemipc, t_timeline *timeline, sem_t *sem)
{
	t_player		*action_player;

	action_player = NULL;
	if (timeline->current_player_id == player->id)
	{
		lock(sem);
		if (count_alive_teams(lemipc) > 1)
			timeline->round++;
		return (TRUE);
	}
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

BOOL		end_turn(t_player *player, t_timeline *timeline, t_lemipc *lemipc, sem_t *sem, int msq_id)
{
	BOOL		res;
	t_msg_buf	msg;

	res = FALSE;
	update_map_pos(lemipc, player);
	if (count_alive_teams(lemipc) > 1)
	{
		res = get_next_player_turn(timeline, lemipc);
		unlock(sem);
		return (res);
	}
	else if (timeline->round == 0)
	{
		printf("There is only one team... i'm waiting for other players "
		"on other teams to have some fun with :(\n");
		unlock(sem);
		return (TRUE);
	}
	unlock(sem);
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
	int			msq_id;
	t_msg_buf	msg;
	int			res_recv;

	ft_memset((void*)&msg.m_text, 0, MSGSZ);
	msq_id = get_message_queue();
	res_recv = 0;
	sem = get_semaphore(SEMAPHORE_NAME);
	timeline = &lemipc->timeline;
	while (player->alive && !lemipc->game_over)
	{
		if (lemipc->timeline.round == 0)
			default_timeline(timeline, lemipc, sem);
		if (my_turn(player, lemipc, timeline, sem))
		{
			printf("Turn (T %d)(P %d)\n", timeline->round, player->id);
			if (lemipc->timeline.round > 0)
				ia_actions_handler(player, lemipc);
			if (!end_turn(player, timeline, lemipc, sem, msq_id))
				end_lemipc(lemipc);
			check_fight_end(lemipc);
		}
		usleep(ACTIONSLOOPTIME * 1000);
	}
	close_semaphore(sem);
	if (!g_global.ended_the_game && lemipc->game_over)
		print_result(lemipc);
	while (g_global.started_the_game)
		usleep(ACTIONSLOOPTIME * 1000);
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
