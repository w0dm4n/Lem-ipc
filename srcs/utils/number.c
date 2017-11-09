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
