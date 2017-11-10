/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:36:24 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/08 05:36:36 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "SDL.h"
# include "SDL_ttf.h"

typedef struct					s_graphic_globals
{
	SDL_Window					*window;
	SDL_GLContext				*context;
	SDL_GLContext				*renderer;
	TTF_Font					*font;
	int							colors[TEAM_SIZE][3];
}								t_graphic_globals;

/*
**	MAIN
*/
int								start_graphic_main(t_lemipc *lemipc);

# define WINDOW_WIDTH 	1024
# define WINDOW_HEIGHT 	1024
# define WINDOW_TITLE	"Lemipc"

# define GRAPHIC_SIZE	900
#endif
