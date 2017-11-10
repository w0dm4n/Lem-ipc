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

#define ARGS_2 t_timeline *timeline, t_lemipc *lemipc, sem_t *sem, int

BOOL		end_turn(t_player *player, ARGS_2 msq_id)
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

#define F10 void	check_fight_end(t_lemipc *lemipc) {
#define F11 if (count_alive_teams(lemipc) <= 1 && lemipc->timeline.round > 0)
#define F12 end_lemipc(lemipc); }
#define FUNC_2 F10 F11 F12

FUNC_2;

#define T_0 get_message_queue(); D(int, msq_id, res_recv);
#define T_1 res_recv = _(ft_memset((void*)&msg.m_text, 0, MSGSZ), 0);
#define T_2 T_0 get_semaphore(SEMAPHORE_NAME); timeline = &lemipc->timeline; T_1
#define T_3 print_result(lemipc) : NULL
#define T_4 (!g_global.ended_the_game && lemipc->game_over) ? T_3
#define T_5 while (g_global.started_the_game) usleep(ACTIONSLOOPTIME * 1000)

void		start_actions_loop(t_player *player, t_lemipc *lemipc)
{
	t_timeline	*timeline;
	sem_t		*sem;
	t_msg_buf	msg;

	sem = T_2;
	while (player->alive && !lemipc->game_over)
	{
		if (!lemipc->pause)
		{
			if (lemipc->timeline.round == 0)
				default_timeline(timeline, lemipc, sem);
			if (my_turn(player, lemipc, timeline, sem))
			{
				printf("(%d) Player %d\n", timeline->round, player->id);
				if (lemipc->timeline.round > 0)
					ia_actions_handler(player, lemipc);
				if (!end_turn(player, timeline, lemipc, sem, msq_id))
					end_lemipc(lemipc);
				check_fight_end(lemipc);
			}
		}
		usleep(ACTIONSLOOPTIME * 1000);
	}
	_(close_semaphore(sem), T_4);
	T_5;
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
