/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 01:59:33 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 02:00:42 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "lists.h"

static void				set_rand(void)
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand((time_t)ts.tv_nsec);
}

static void				init_utilities()
{
	set_rand();
	catch_signal();
	g_global.player = NULL;
	g_global.lemipc = NULL;
	g_global.started_the_game = FALSE;
	g_global.ended_the_game = FALSE;
}

int						main(int argc, char **argv)
{
	int			segment;
	int			team_id;
	t_lemipc	*lemipc;

	team_id = 0;
	segment = 0;
	lemipc = NULL;
	init_utilities();
	if (argc == 2)
	{
		team_id = ft_atoi(argv[1]);
		if ((segment = get_active_segment(get_segment_size())) != SEGMENT_ERROR
			&& (lemipc = get_lemipc(segment)) != NULL)
			timeline(add_new_player(team_id, lemipc), lemipc);
		else
			init_lemipc(ft_atoi(argv[1]));
	}
	else
		printf("Please give me a team id as argument !\n");
	return (0);
}
