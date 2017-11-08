/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 01:43:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 01:43:10 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			handle_signal(int signal)
{
	sem_t		*sem;

	sem = get_semaphore(SEMAPHORE_NAME);
	if (g_global.player != NULL && g_global.lemipc != NULL)
	{
		lock(sem);
		die(g_global.player, g_global.lemipc);
		unlock(sem);
		if (g_global.lemipc->players_length <= 0 ||
			count_alive_players(g_global.lemipc) <= 0)
			end_lemipc(g_global.lemipc);
	}
	close_semaphore(sem);
	exit(EXIT_SUCCESS);
}

void			catch_signal()
{
	int		i;

	i = 0;
	while (i < _NSIG)
		signal(i++, handle_signal);
}
