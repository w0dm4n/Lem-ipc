/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 02:00:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 02:00:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>

# include "../libft/includes/libft.h"

# define BOOL				ushort
# define TRUE				1
# define FALSE				0
# define SEGMENT_ERROR		-1
# define IPC_KEY			"l3m1pc"
# define SEMAPHORE_NAME		"/l3m1pc"
# define MAP_SIZE			50
# define FREE_CELL			0
# define PLAYERS_SIZE		10000

typedef struct		s_player
{
	ushort			id;
	ushort			x_position;
	ushort			y_position;
	BOOL			alive;
	int				team_id;
}					t_player;

typedef struct		s_lemipc
{
	ushort			sequence_id;
	int				segment_id;
	ushort			map[MAP_SIZE][MAP_SIZE];
	t_player		players[PLAYERS_SIZE];
	ushort			players_length;
}					t_lemipc;

/*
**	LEMIPC
*/
void			init_lemipc();
t_lemipc		*get_lemipc(int seg_id);
t_lemipc		*alloc_lemipc(int seg_id, sem_t *sem);

/*
**	SEGMENT
*/
int				get_active_segment(int size);
int				create_segment(int size);
int				delete_segment(int segment_id);
void			*get_segment_memory(int segment_id);
int				get_segment_size();

/*
**	SEMAPHORE
*/
sem_t 			*create_semaphore(char *semaphore_name);
sem_t 			*get_semaphore(char *semaphore_name);
BOOL			delete_semaphore(char *name);
BOOL			lock(sem_t *sem);
BOOL			unlock(sem_t *sem);

/*
**	UTILS
*/
key_t			get_ipc_key(char *ascii_key);
int				get_random(int max);

/*
**	MAP
*/
void			init_map(t_lemipc *lemipc);
t_player		*get_player_on_cell(t_lemipc *lemipc, int x, int y);
void			update_pos(t_lemipc *lemipc, t_player *player);

/*
**	PLAYER
*/
t_player		*find_player_by_id(int id, t_lemipc *lemipc);
t_player		*add_new_player(int team_id, t_lemipc *lemipc);

/*
**	TEAM
*/
// t_team			*get_team(int id, t_lemipc *lemipc);
#endif
