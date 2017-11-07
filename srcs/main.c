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

void					print_y(t_lemipc* lemipc, int x)
{
	int y = 0;
	while (y < MAP_SIZE) {
		printf("%d\n", lemipc->map[x][y++]);
	}
}

static void				set_rand()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
}

int						main(int argc, char **argv)
{
	int		segment;
	int		team_id;

	set_rand();
	team_id = 0;
	if (argc == 2)
	{
		team_id = ft_atoi(argv[1]);
		if ((segment = get_active_segment(get_segment_size())) != SEGMENT_ERROR)
		{
			sem_t		*sem;
			t_lemipc	*lemipc = get_lemipc(segment);
			// t_team		*team;

			sem = get_semaphore(SEMAPHORE_NAME);
			t_player *player = add_new_player(team_id, lemipc);
			if (player)
			{
				printf("Player id: %d, my x position: %d, my y position: %d\n",
				player->id, player->x_position, player->y_position);
			}
			else {
				printf("Map is full cant have some new players !\n");
			}
			//if ((team = get_team(team_id, lemipc)) == NULL)
			// team = create_team(team_id, lemipc);
			// lock(sem);
			// printf("Segment id %d found !\n", segment);
			// if ((lemipc = get_lemipc(segment)) != NULL)
			// {
			// 	lemipc->sequence_id += 1;
			// 	int x = 0;
			// 	int y = 0;
			// 	while (x < MAP_SIZE) {
			// 		print_y(lemipc, x++);
			// 	}
			// }
			// if (delete_segment(segment) != SEGMENT_ERROR)
			// {
			// 	printf("Segment id %d deleted\n", segment);
			// }
			// unlock(sem);
		}
		else
			init_lemipc(ft_atoi(argv[1]));
	}
	else
		printf("Please give me a team id as argument !\n");
	return (0);
}
