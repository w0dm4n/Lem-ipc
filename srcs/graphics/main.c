/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:33:54 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 05:35:29 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "graphics.h"

static t_graphic_globals		graphic_globals;

float							get_square_len(float *start_pos)
{
	return (start_pos[0] + 1.0 / MAP_SIZE * GRAPHIC_SIZE);
}

int								*get_player_position(t_player *player)
{
	int		*pos;
	float start_pos[2];

	start_pos[0] = 1.0;
	start_pos[1] = 1.0;
	float square_len = get_square_len((int*)&start_pos);
	if (!(pos = (int*)malloc(sizeof(int*) * 2)))
		return (NULL);
	pos[0] = player->x_position * square_len;
	pos[1] = player->y_position * square_len;
	return (pos);
}

int								*get_team_color(int team_id)
{
	if (graphic_globals.colors[team_id][0] == -1)
	{
		graphic_globals.colors[team_id][0] = get_random(255);
		graphic_globals.colors[team_id][1] = get_random(255);
		graphic_globals.colors[team_id][2] = get_random(255);
	}
	return (&graphic_globals.colors[team_id]);
}

void							render_window(t_lemipc *lemipc)
{
	SDL_GL_MakeCurrent(graphic_globals.window, graphic_globals.context);
	SDL_SetRenderDrawColor(graphic_globals.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect r = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_RenderFillRect(graphic_globals.renderer, &r);
	int i = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive)
		{
			int *pos = get_player_position(&lemipc->players[i]);
			int *color = get_team_color(lemipc->players[i].team_id);
			if (pos && color)
			{
				SDL_SetRenderDrawColor(graphic_globals.renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
				SDL_Rect r = { pos[0], pos[1], 10, 10};
				SDL_RenderFillRect(graphic_globals.renderer, &r);
				free(pos);
			}
		}
		i++;
	}
	SDL_GL_SwapWindow(graphic_globals.window);
}

void								fill_colors(void)
{
	int		i;

	i = 0;
	while (i < TEAM_SIZE)
	{
		graphic_globals.colors[i][0] = -1;
		graphic_globals.colors[i][1] = -1;
		graphic_globals.colors[i][2] = -1;
		i++;
	}
}

int										start_graphic_main(t_lemipc *lemipc)
{
	SDL_Event		event;

	fill_colors();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return (-1);
	}
	graphic_globals.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, \
	SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, \
	SDL_WINDOW_OPENGL);
	graphic_globals.context = SDL_GL_CreateContext(graphic_globals.window);
	graphic_globals.renderer = SDL_CreateRenderer(graphic_globals.window, -1, 0);
	while (!lemipc->game_over)
	{
		while (SDL_PollEvent(&event))
			;
		render_window(lemipc);
		SDL_Delay(2);
	}
	SDL_GL_DeleteContext(graphic_globals.context);
	SDL_DestroyWindow(graphic_globals.window);
	SDL_Quit();
	return (0);
}
