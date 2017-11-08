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

#include "SDL.h"
#include "all.h"
#include "graphics.h"

static SDL_Window		*g_window;
static SDL_GLContext	*g_context;
static SDL_GLContext	*g_renderer;

void		render_window(void)
{
	SDL_GL_MakeCurrent(g_window, g_context);
	SDL_SetRenderDrawColor(g_renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(g_renderer, 100, 100, 200, 200);
	SDL_GL_SwapWindow(g_window);
}

int			start_graphic_main(t_lemipc *lemipc)
{
	SDL_Event		event;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return (-1);
	}
	g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, \
	SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, \
	SDL_WINDOW_OPENGL);
	g_context = SDL_GL_CreateContext(g_window);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	while (!lemipc->game_over)
	{
		while (SDL_PollEvent(&event))
			;
		render_window();
		SDL_Delay(2);
	}
	SDL_GL_DeleteContext(g_context);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	return (0);
}
