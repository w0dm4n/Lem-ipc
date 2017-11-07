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
	init_map(lemipc);
	return (lemipc);
}

void		init_lemipc(int team_id)
{
	int				segment;
	sem_t			*sem;
	t_lemipc		*lemipc;

	if ((segment = create_segment(get_segment_size() + 10000)) != SEGMENT_ERROR &&
		(sem = create_semaphore(SEMAPHORE_NAME)) != SEM_FAILED)
	{
		if ((lemipc = alloc_lemipc(segment, sem)) != NULL)
		{
			t_player *player = add_new_player(team_id, lemipc);
			printf("Player id: %d\n", player->id);
		}
		// delete_segment(segment);
		// delete_semaphore(SEMAPHORE_NAME);
	}
	else
	{
		printf("%s: %d\n", strerror(errno), get_segment_size());
	}
}
