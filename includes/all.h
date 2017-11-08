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
# include <unistd.h>
# include <signal.h>

# include "../libft/includes/libft.h"

# define BOOL				ushort
# define TRUE				1
# define FALSE				0
# define SEGMENT_ERROR		-1
# define IPC_KEY			"l3m1pc"
# define SEMAPHORE_NAME		"/l3m1pc"
# define MAP_SIZE			50
# define FREE_CELL			0
# define TEAM_SIZE			1024
# define PLAYERS_SIZE		10000
# define ACTIONSLOOPTIME	100
# define HISTORY			5096
# define SPAWN_POS_TIME		100
# define _NSIG				65
# define FORNORMMAPSIZE		MAP_SIZE
# define FORNORMSPAWNPOS	SPAWN_POS_TIME

typedef struct		s_player
{
	ushort			id;
	ushort			x_position;
	ushort			y_position;
	BOOL			alive;
	int				team_id;
}					t_player;

typedef struct		s_timeline
{
	int				round;
	ushort			current_player_id;
	ushort			history_players[HISTORY];
	ushort			history_count;
}					t_timeline;

typedef struct		s_lemipc
{
	ushort			sequence_id;
	int				segment_id;
	ushort			map[MAP_SIZE][MAP_SIZE];
	t_player		players[PLAYERS_SIZE];
	ushort			players_length;
	t_timeline		timeline;
	BOOL			game_over;
}					t_lemipc;

typedef struct		s_target
{
	ushort			id;
	ushort			x_position;
	ushort			y_position;
}					t_target;

typedef struct		s_global
{
	t_player		*player;
	t_lemipc		*lemipc;
	BOOL			ended_the_game;
}					t_global;

t_global			g_global;
/*
**	LEMIPC
*/
void			init_lemipc();
t_lemipc		*get_lemipc(int seg_id);
t_lemipc		*alloc_lemipc(int seg_id, sem_t *sem);
void			end_lemipc(t_lemipc *lemipc);
void			print_result(t_lemipc *lemipc);

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
BOOL			close_semaphore(sem_t *sem);
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
t_player		*get_player_on_cell(t_lemipc *lemipc, int x, int y);
void			update_map_pos(t_lemipc *lemipc, t_player *player);

/*
**	PLAYER
*/
t_player		*find_player_by_id(int id, t_lemipc *lemipc);
t_player		*add_new_player(int team_id, t_lemipc *lemipc);
int				count_alive_players(t_lemipc *lemipc);
t_player		*get_first_alive_player(t_lemipc *lemipc);
void			die(t_player *player, t_lemipc *lemipc);
void			set_pos(int x, int y, t_player *player, t_lemipc *lemipc);

/*
**	TIMELINE
*/
void			init_timeline(t_lemipc *lemipc);
void			timeline(t_player *player, t_lemipc *lemipc);
BOOL			get_next_player_turn(t_timeline *timeline, t_lemipc *lemipc);

/*
**	SIGNAL
*/
void			catch_signal();

/*
**	IA
*/
void			ia_actions_handler(t_player *player, t_lemipc *lemipc);
t_player		*find_nearest_enemy(t_player *player, t_lemipc *lemipc);
void			move_to_enemy(t_player *player, t_player *target, t_lemipc *lemipc);

/*
**	MAP
*/
BOOL			is_cell_free(int x, int y, t_lemipc *lemipc);
void			reset_map_pos(t_lemipc *lemipc, t_player *player);
#endif
