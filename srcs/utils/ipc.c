/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ipc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 04:07:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 04:07:26 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

key_t			get_ipc_key(char *ascii_key)
{
	int		i;
	key_t	key;

	i = 0;
	key = 0;
	while (ascii_key[i])
		key += (int)ascii_key[i++];
	return (key);
}
