/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:44:55 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 03:44:57 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int				get_segment_size()
{
	return ((MAP_SIZE * 2) + sizeof(struct s_lemipc));
}

int				get_active_segment(int size)
{
	return (shmget(get_ipc_key(IPC_KEY), size, 0666));
}

int				create_segment(int size)
{
	return (shmget(get_ipc_key(IPC_KEY), size, IPC_CREAT | 0666));
}

int				delete_segment(int segment_id)
{
	return (shmctl(segment_id, IPC_RMID, 0));
}

void			*get_segment_memory(int segment_id)
{
	return (shmat(segment_id, 0, 0));
}
