/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:52:46 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 03:52:51 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "lists.h"
#include "graphics.h"

t_lemipc		*get_lemipc(int seg_id)
{
	return ((t_lemipc*)get_segment_memory(seg_id));
}

t_lemipc		*alloc_lemipc(int seg_id, sem_t *sem)
{
	void		*shm;
	t_lemipc	*lemipc;

	if (!(shm = get_segment_memory(seg_id)))
		return (NULL);
	lemipc = (t_lemipc*)shm;
	lemipc->segment_id = seg_id;
	lemipc->sequence_id = 0;
	lemipc->players_length = 0;
	lemipc->game_over = FALSE;
	init_map(lemipc);
	init_timeline(lemipc);
	return (lemipc);
}

void			print_result(t_lemipc *lemipc)
{
	t_player		*winner;

	if ((winner = get_first_alive_player(lemipc)) != NULL)
	{
		printf("The game is over.. and the winner team is the team %d !\n",
		winner->team_id);
	}
	else
	{
		printf("The game is over.. and no one has won !\n");
	}
}

void			end_lemipc(t_lemipc *lemipc)
{
	sem_t		*sem;

	g_global.ended_the_game = TRUE;
	sem = get_semaphore(SEMAPHORE_NAME);
	lock(sem);
	lemipc->game_over = TRUE;
	print_result(lemipc);
	unlock(sem);
	delete_semaphore(SEMAPHORE_NAME);
	delete_segment(lemipc->segment_id);
}

void			init_lemipc(int team_id)
{
	int				segment;
	sem_t			*sem;
	t_lemipc		*lemipc;
	pid_t			pid;

	pid = 0;
	delete_semaphore(SEMAPHORE_NAME);
	if ((segment = create_segment(get_segment_size())) != SEGMENT_ERROR &&
		(sem = create_semaphore(SEMAPHORE_NAME)) != SEM_FAILED)
	{
		if ((lemipc = alloc_lemipc(segment, sem)) != NULL)
		{
			pid = fork();
			if (pid == 0)
				timeline(add_new_player(team_id, lemipc), lemipc);
			else if (pid > 0)
				start_graphic_main(lemipc);
		}
	}
	else
		printf("An error occured on shared memory allocation: %s: of size %d\n",
		strerror(errno), get_segment_size());
}
