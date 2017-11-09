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

void		fill_zero_finder(t_player *players, int len)
{
	int	i;

	i = 0;
	while (i < len)
		players[i++].id = 0;
}

static void		find_players_beside(t_player *players_beside, t_player *player, t_lemipc *lemipc)
{
	int			count_players_beside;

	fill_zero_finder((t_player*)players_beside, MAX_POSSIBLE_PLAYERS_BESIDE);
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

int		count_enemies_beside(t_player *players_beside, t_player *player)
{
	int		i;
	int		count_players_beside;

	// check team to avoid 1v1v1 and dying..
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

void		chose_action(t_player *player, t_player *players, t_lemipc *lemipc)
{
	t_player	*target;
	int			enemies_around;
	int			mates_around;

	target = NULL;
	enemies_around = count_ennemies_around(players, player);
	mates_around = count_mates_around(players, player);

	if (enemies_around >= 1 && mates_around == 0)
	{
		printf("j'ss tout seul a leeeeeeeeeed\n");
		// find_nearest_friend
	}
	else if ((mates_around + 1) > enemies_around)
	{
		printf("Let's kill the mother fuqueur\n");
		// get the mother fucker
	}
	else if (enemies_around > (mates_around + 1))
	{
		printf("Let's run like a pussy !\n");
		// find_farther_friend
	}
	else
	{
		printf("I dont know what to do so i will just follow an enemy.\n");
	}
	if ((target = find_nearest_enemy(player, lemipc)) != NULL)
		move_to_enemy(player, target, lemipc);
	printf("Enemies: %d, mates: %d\n", enemies_around, mates_around);
}

void		ia_actions_handler(t_player *player, t_lemipc *lemipc)
{
	t_player	players_beside[MAX_POSSIBLE_PLAYERS_BESIDE];
	t_player	players_around[MAX_POSSIBLE_PLAYERS_AROUND];

	find_players_beside((t_player*)&players_beside, player, lemipc);
	find_players_around((t_player*)&players_around, player, lemipc, 10);
	chose_action(player, (t_player*)&players_around, lemipc);
	// if (count_enemies_beside((t_player*)&players_beside, player) >= MAX_ENEMY_BEFORE_DEATH)
	// 	die(player, lemipc);
}
