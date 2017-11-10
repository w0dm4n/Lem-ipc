/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeline_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:45:10 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/10 15:45:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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

#define F1 void reset_timeline(t_lemipc *lemipc, sem_t *sem) { lock(sem);
#define F2 reset_history_timeline(&lemipc->timeline, lemipc);
#define F3 unlock(sem); }
#define FUNC F1 F2 F3

FUNC;

void		default_timeline(t_timeline *timeline, t_lemipc *lemipc, sem_t *sem)
{
	t_player	*current;

	current = NULL;
	if (timeline->current_player_id == 0)
		reset_timeline(lemipc, sem);
}

#define ARGS t_player *player, t_lemipc *lemipc, t_timeline

BOOL		my_turn(ARGS *timeline, sem_t *sem)
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
