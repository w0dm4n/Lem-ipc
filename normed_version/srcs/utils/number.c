/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:00:33 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 09:00:36 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "graphics.h"

int				get_random(int max)
{
	return (rand() % max);
}

void			fill_zero(int *array, int len)
{
	int		i;

	i = 0;
	while (i < len)
		array[i++] = 0;
}

#define F1 float get_square_len(float *start_pos)
#define F2 { return (start_pos[0] + 1.0 / MAP_SIZE * GRAPHIC_SIZE); }
#define FUNC F1 F2

FUNC;

int				*get_player_position(t_player *player)
{
	float		start_pos[2];
	float		square_len;
	int			*pos;

	start_pos[0] = 1.0;
	start_pos[1] = 1.0;
	square_len = get_square_len((int*)&start_pos);
	if (!(pos = (int*)malloc(sizeof(int*) * 2)))
		return (NULL);
	pos[0] = player->x_position * square_len;
	pos[1] = player->y_position * square_len;
	return (pos);
}
