/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:43:06 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/16 15:43:07 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// new term || 
// clean str




#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <unistd.h>
# include "vm.h"

// Scrolling names
#define LEFT_D 1
#define RIGHT_D 0
#define MAX_NAME_LEN 30
#include <sys/time.h>
// Scrolling names


# define W_HEIGHT 68
# define W_WIDTH 251
# define START_X 2
# define LEFT_W 0
# define PLAYER_1 1
# define PLAYER_2 2
# define PLAYER_3 3
# define PLAYER_4 4
# define CARRY_P1 10
# define CARRY_P2 20
# define CARRY_P3 30
# define CARRY_P4 40


typedef struct				s_scrolling_controls
{
	WINDOW					*window;
	int						direction;
	int						key;
	unsigned long long		seconds;
} 							t_scrolling_controls;

typedef struct 				s_scroll_name
{
	WINDOW					*window;
	char					*full_name;
	int						full_name_len;
	char					*displayed_name;
	char					*hidden_name;
	int						hidden_len;
	struct s_scroll_name	*next;
}							t_scroll_name;

typedef struct				s_vdata
{
	WINDOW					*left_window;
	WINDOW					*right_window;
	int						key;
	int						paused;
	unsigned long long		sec;
	t_scroll_name			*scrolling_names;
	t_scrolling_controls	*scrolling_controls;
	unsigned long long		time;
	unsigned long long		time2;

	int						user_input;
	char					user_cycle[10];
	int 					index;
	int skip;

	int 					vasya;
}							t_vdata;
void						show_carries(t_vdata *vdata, t_session *game);
void    					show_right(t_vdata *vdata, t_session *game, t_champ *champs);
void						show_left(t_vdata *vdata, t_session *game, t_champ *champs);
void 						print_player_code(WINDOW *left_window, int y, int x, t_uchar n, int player);
int							visu_initializing(t_vdata *vdata, t_arg *arg, t_champ *champs, int total_champs);
void						set_champs_names_to_scrolling(t_vdata *vdata, t_champ *champs, int total_champs);
int							visu_finalizing		(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg);
int							visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs,t_arg *arg);
void						show_players(WINDOW *nbr_win, t_champ *champs, int *i);
void						playback_controls(t_vdata *vdata, t_session *game, t_champ *champs);
void	add_scrolling_name(t_scroll_name *name, t_scroll_name **scrolling_name);
void						scrolling_controls(t_vdata *vdata, int x, int y);
void						scrolling_name(t_vdata *vdata, t_uchar *player_name, int x, int y);
void						scrolling_of_the_names(t_vdata *vdata);
void						scrolling_finalizing(t_vdata *vdata);
void						music_player();
#endif
