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

#define GLOBAL static t_graphic_globals		graphic_globals

GLOBAL;

#define F10 int *get_team_color(int team_id) {
#define F11 if (graphic_globals.colors[team_id][0] == -1) {
#define F12 graphic_globals.colors[team_id][0] = get_random(255);
#define F13 graphic_globals.colors[team_id][1] = get_random(255);
#define F14 graphic_globals.colors[team_id][2] = get_random(255);
#define F15 } return (&graphic_globals.colors[team_id]); }
#define FUNC_3 F10 F11 F12 F13 F14 F15

FUNC_3;

#define RQUAD SDL_Rect renderQuad = { x, y, text_surface->w, text_surface->h }
#define T SDL_CreateTextureFromSurface(graphic_globals.renderer, text_surface)

void									print_text(char *string, int x, int y)
{
	SDL_Surface		*text_surface;
	SDL_Texture		*text;
	SDL_Color		text_color;

	text_color = (SDL_Color){ 255, 255, 255, 0 };
	if (graphic_globals.font)
	{
		text_surface = \
		TTF_RenderText_Solid(graphic_globals.font, string, text_color);
		text = T;
		RQUAD;
		SDL_RenderCopy(graphic_globals.renderer, text, NULL, &renderQuad);
	}
	else
		printf("TTF_OpenFont: %s\n", TTF_GetError());
}

void									print_alive_players(char *base, \
	t_lemipc *lemipc)
{
	int		i;
	int		players;

	i = 0;
	players = 0;
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive)
			players++;
		i++;
	}
	print_text(base, 100, 0);
	print_text(ft_itoa(players), 250, 0);
}

#define R		SDL_Rect r = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }; i = 0
#define R_2		SDL_Rect r = { pos[0], pos[1], 10, 10}
#define POS		int *pos = get_player_position(&lemipc->players[i])
#define COLOR	int *color = get_team_color(lemipc->players[i].team_id)

void									render_window(t_lemipc *lemipc)
{
	int		i;

	R;
	SDL_GL_MakeCurrent(graphic_globals.window, graphic_globals.context);
	SDL_SetRenderDrawColor(graphic_globals.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(graphic_globals.renderer, &r);
	print_alive_players("Alive players: ", lemipc);
	while (i < PLAYERS_SIZE)
	{
		if (lemipc->players[i].alive)
		{
			POS;
			COLOR;
			if (pos && color)
			{
				SDL_SetRenderDrawColor(graphic_globals.renderer, color[0], \
					color[1], color[2], SDL_ALPHA_OPAQUE);
				R_2;
				SDL_RenderFillRect(graphic_globals.renderer, &r);
				free(pos);
			}
		}
		i++;
	}
	SDL_GL_SwapWindow(graphic_globals.window);
}

#define F5 void fill_colors(void) { int i; i=0;
#define F6 while (i < TEAM_SIZE) { graphic_globals.colors[i][0] = -1;
#define F7 graphic_globals.colors[i][1] = -1;graphic_globals.colors[i][2] = -1;
#define F8 i++; } }
#define FUNC2 F5 F6 F7 F8

FUNC2;

#define A graphic_globals.font=TTF_OpenFont("assets/FiraSans-Regular.ttf", 24)
#define B graphic_globals.context=SDL_GL_CreateContext(graphic_globals.window)
#define D SDL_CreateRenderer
#define C graphic_globals.renderer = D(graphic_globals.window, -1, 0)
#define GLOBAL_DECLARATION _(A, B, C)

void									print_end(char *base, \
	t_lemipc *lemipc)
{
	t_player	*player;
	int			i;

	R;
	SDL_GL_MakeCurrent(graphic_globals.window, graphic_globals.context);
	SDL_SetRenderDrawColor(graphic_globals.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(graphic_globals.renderer, &r);
	if ((player = get_first_alive_player(lemipc)) != NULL)
	{
		print_text(base, 300, 500);
		print_text(ft_itoa(player->team_id), 780, 500);
	}
}

#define F20 void catch_keys(SDL_Event *event, int *quit, t_lemipc *lemipc) {
#define F21 switch (event->type) { case SDL_QUIT: *quit = TRUE; break;
#define F22 case SDL_KEYUP: switch(event->key.keysym.sym) {
#define F23 case SDLK_SPACE: if (!lemipc->pause) lemipc->pause = TRUE;
#define F24 else lemipc->pause = FALSE; break; } break; } }
#define FUNC_5 F20 F21 F22 F23 F24

#define GB graphic_globals
#define F30 SDL_GL_MakeCurrent(GB.window, GB.context)
#define F31 SDL_SetRenderDrawColor(GB.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)
#define F32 print_end("The game is over.. the winner is the team: ", lemipc)
#define F33 SDL_GL_SwapWindow(graphic_globals.window)

/*
**	Please forgive me lord
*/
FUNC_5;
#define TN (!lemipc->game_over) ? render_window(lemipc) : _(F30, F31, F32, F33)

int										start_graphic_main(t_lemipc *lemipc)
{
	SDL_Event		event;
	BOOL			quit;

	quit = FALSE;
	fill_colors();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 || TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return (-1);
	}
	graphic_globals.window = \
	SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, \
	SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, \
	SDL_WINDOW_OPENGL);
	GLOBAL_DECLARATION;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
			catch_keys(&event, &quit, lemipc);
		_(TN, SDL_Delay(2));
	}
	_(SDL_GL_DeleteContext(graphic_globals.context), \
	SDL_DestroyWindow(graphic_globals.window), SDL_Quit());
	return (0);
}
