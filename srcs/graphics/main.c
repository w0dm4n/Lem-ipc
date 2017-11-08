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

int			start_graphic_main(t_lemipc *lemipc)
{
	SDL_Event		event;
	SDL_Surface		*screen;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);
	screen = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 0, 0);
	while (!lemipc->game_over)
	{
		if (SDL_PollEvent(&event))
		{

		}
	}
	SDL_Quit();
	return (0);
}
