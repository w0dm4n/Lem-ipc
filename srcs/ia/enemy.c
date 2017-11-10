/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 07:12:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/10 07:13:07 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		get_all_possible_enemy(t_player *player, t_target *targets, \
	t_lemipc *lemipc)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	fill_zero_targets(targets);
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive && lemipc->players[i].team_id != \
			player->team_id)
		{
			targets[len].id =  lemipc->players[i].id;
			targets[len].x_position =  lemipc->players[i].x_position;
			targets[len].y_position =  lemipc->players[i].y_position;
			len++;
		}
		i++;
	}
	return (len);
}

t_player		*find_nearest_enemy(t_player *player, t_lemipc *lemipc)
{
	t_target	targets[PLAYERS_SIZE];
	int			possible_target;
	t_player	*target;
	int			radius;

	target = NULL;
	possible_target = 0;
	radius = 5;
	if ((possible_target = get_all_possible_enemy(player, (t_target*)&targets, lemipc)) > 0)
	{
		while (radius < (FORNORMMAPSIZE * 2))
		{
			if ((target = find_player_by_radius(radius, player, (t_target*)&targets, possible_target, lemipc)) != NULL)
				return (target);
			radius += 5;
		}
	}
	return (NULL);
}
