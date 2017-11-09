/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_actions_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:03:03 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 10:03:09 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void		fill_zero_players(t_player *players_beside)
{
	int	i;

	i = 0;
	while (i < MAX_POSSIBLE_PLAYERS_BESIDE)
		players_beside[i++].id = 0;
}

static void		find_players_beside(t_player *players_beside, t_player *player, t_lemipc *lemipc)
{
	int			count_players_beside;

	fill_zero_players((t_player*)players_beside);
	count_players_beside = 0;

	if (lemipc->map[player->x_position - 1][player->y_position] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position - 1, player->y_position);
	if (lemipc->map[player->x_position - 1][player->y_position - 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position - 1, player->y_position - 1);
	if (lemipc->map[player->x_position - 1][player->y_position + 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position - 1, player->y_position + 1);
	if (lemipc->map[player->x_position + 1][player->y_position] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position + 1, player->y_position);
	if (lemipc->map[player->x_position + 1][player->y_position - 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position + 1, player->y_position - 1);
	if (lemipc->map[player->x_position + 1][player->y_position + 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position + 1, player->y_position + 1);
	if (lemipc->map[player->x_position][player->y_position + 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position, player->y_position + 1);
	if (lemipc->map[player->x_position][player->y_position - 1] != FREE_CELL)
		players_beside[count_players_beside++] = *get_player_on_cell(lemipc, player->x_position, player->y_position - 1);
}

int		count_mates_around(t_player *players_beside, t_player *player)
{
	int		i;
	int		count_mates_around;

	i = 0;
	count_mates_around = 0;
	while (i < MAX_POSSIBLE_PLAYERS_BESIDE)
	{
		if (players_beside[i].id != 0 && players_beside[i].team_id == player->team_id)
			count_mates_around++;
		i++;
	}
	return (count_mates_around);
}

int		count_enemies_beside(t_player *players_beside, t_player *player)
{
	int		i;
	int		count_players_beside;

	i = 0;
	count_players_beside = 0;
	while (i < MAX_POSSIBLE_PLAYERS_BESIDE)
	{
		if (players_beside[i].id != 0 && players_beside[i].team_id != player->team_id)
			count_players_beside++;
		i++;
	}
	return (count_players_beside);
}

void		ia_actions_handler(t_player *player, t_lemipc *lemipc)
{
	t_player	*target;
	t_player	players_beside[MAX_POSSIBLE_PLAYERS_BESIDE];
	int			enemy_beside;
	int			mates_around;

	find_players_beside((t_player*)&players_beside, player, lemipc);
	enemy_beside = count_enemies_beside((t_player*)&players_beside, player);
	// mates_around = count_mates_around((t_player*)&players_beside, player);
	if ((target = find_nearest_enemy(player, lemipc)) != NULL)
	{
		move_to_enemy(player, target, lemipc);
	}
	if (enemy_beside >= MAX_ENEMY_BEFORE_DEATH)
		die(player, lemipc);
}
