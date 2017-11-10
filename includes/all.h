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
# include <sys/time.h>

# include "../libft/includes/libft.h"

# define BOOL								int
# define TRUE								1
# define FALSE								0
# define SEGMENT_ERROR						-1
# define MSQ_ERROR							-1
# define IPC_KEY							"l3m1pc"
# define MSGQ_KEY							"qu3u3_l3m1pc"
# define SEMAPHORE_NAME						"/l3m1pc"
# define MAP_SIZE							50
# define FREE_CELL							0
# define TEAM_SIZE							1024
# define PLAYERS_SIZE						10000
# define ACTIONSLOOPTIME					1
# define HISTORY							5096
# define SPAWN_POS_TIME						100
# define _NSIG								65
# define FORNORMMAPSIZE						MAP_SIZE
# define FORNORMSPAWNPOS					SPAWN_POS_TIME
# define MAX_POSSIBLE_PLAYERS_AROUND		20
# define MAX_POSSIBLE_PLAYERS_BESIDE		8
# define MAX_ENEMY_BEFORE_DEATH				2
# define MAX_TURN_TIME						1
# define MSGSZ								128
# define MSG_TURN							"CURRENT_PLAYER_TURN\0"

typedef struct		s_msg_buf
{
	long    		m_type;
	char    		m_text[MSGSZ];
}					t_msg_buf;

typedef struct		s_player
{
	int				id;
	int				x_position;
	int				y_position;
	BOOL			alive;
	int				team_id;
}					t_player;

typedef struct		s_timeline
{
	int				round;
	int				current_player_id;
	int				history_players[HISTORY];
	int				history_count;
}					t_timeline;

typedef struct		s_lemipc
{
	int				sequence_id;
	int				segment_id;
	int				map[MAP_SIZE][MAP_SIZE];
	t_player		players[PLAYERS_SIZE];
	int				players_length;
	t_timeline		timeline;
	BOOL			game_over;
}					t_lemipc;

typedef struct		s_target
{
	int				id;
	int				x_position;
	int				y_position;
}					t_target;

typedef struct		s_global
{
	BOOL			started_the_game;
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
key_t			convert_to_key(char *ascii_key);
int				get_random(int max);
void			fill_zero(int *array, int len);

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
void			move_to_target(t_player *player, t_player *target, t_lemipc *lemipc);
void			fill_zero_finder(t_player *players_beside, int len);

/*
**	ENEMY
*/
int				get_all_possible_enemy(t_player *player, t_target *targets, t_lemipc *lemipc);
t_player		*find_nearest_enemy(t_player *player, t_lemipc *lemipc);

/*
**	MATES
*/
int				count_mates(t_player *player, t_lemipc *lemipc);
t_player		*find_nearest_friend(t_player *player, t_lemipc *lemipc);

/*
**	MAP
*/
BOOL			is_cell_free(int x, int y, t_lemipc *lemipc);
void			reset_map_pos(t_lemipc *lemipc, t_player *player);

/*
**	RADIUS
*/
void			find_players_around(t_player *players, t_player *player, t_lemipc *lemipc, int radius);
int				count_players_around(t_player *players);
int				count_ennemies_around(t_player *players, t_player *player);
int				count_mates_around(t_player *players, t_player *player);
t_player		*find_player_by_radius(int radius, t_player *player, t_target *targets, int len, t_lemipc *lemipc);

/*
**	PATHFINDING
*/
void			fill_zero_targets(t_target *targets);
int				get_all_possible_enemy(t_player *player, t_target *targets, t_lemipc *lemipc);
int				get_all_possible_players(t_player *player, t_target *targets, t_lemipc *lemipc);

/*
**	MESSAGE_QUEUE
*/
void			delete_all_messages_queues(void);
int				create_message_queue(void);
int				get_message_queue(void);
void			build_message(int type, char *data, t_msg_buf *msg);
#endif
