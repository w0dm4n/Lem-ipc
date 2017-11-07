/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teams.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 06:12:13 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 06:12:14 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// void		add_team(t_team *team, t_lemipc *lemipc)
// {
// 	t_teams		*teams;
//
// 	teams = lem_ipc->teams;
// 	if (teams != NULL)
// 	{
// 		while (teams->next)
// 			teams = teams->next;
// 		ft_memcpy((void*)teams + sizeof(struct s_team), team, sizeof(struct s_team));
// 		teams->next = (void*)teams + sizeof(struct s_team);
// 	}
// 	else
// 	{
// 		ft_memcpy((void*)teams, team, sizeof(struct s_team));
// 	}
// }
//
// t_team		*create_team(int team_id, t_lemipc *lemipc)
// {
// 	t_team	*team;
//
// 	if (!(team = alloc_team(team_id)))
// 	{
// 		add_team(team, lemipc);
// 		return (team);
// 	}
// 	return (NULL);
// }
