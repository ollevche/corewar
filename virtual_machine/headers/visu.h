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
#define MAX_NAME_LEN 20
#include <sys/time.h>
// Scrolling names


# define W_HEIGHT 78
# define W_WIDTH 251
# define START_X 2
# define GRAY 0
# define GRAY_B 100
# define PLAYER_1 1
# define PLAYER_2 2
# define PLAYER_3 3
# define PLAYER_4 4
# define CARRY_P1 10
# define CARRY_P2 20
# define CARRY_P3 30
# define CARRY_P4 40


//COLORS
# define COLOR_JA 4181

//KEYS
# define ESC 27
# define LEFT 260
# define RIGHT 261
# define ENTER '\n'
# define E 101
# define Y 121
# define N 110
# define S 115
# define M 109
# define SPACE 32
# define BACKSPACE 127
# define NUMBER_KEYS (vdata->key >= '0' && vdata->key <= '9')
# define KEY(x) (vdata->key == x)
# define ERASE_KEY (vdata->key = -1)
//KEYS

//ALERT WINDOWS
# define CUSTOM_CYCLE 1
# define GAME_OVER 2
# define EXIT 3
# define ACTIVE_ALERT(x) x == CUSTOM_CYCLE || x == GAME_OVER || x == GAME_OVER


//LIVE BAR
# define BAR_LEN 150

# define AUTHOR_LEN 186

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

typedef struct 				s_live_bar
{
	WINDOW					*window;
	char					line[BAR_LEN];
	int						*lives;
	int						prev_lives;
	int						prev_line;
	struct s_live_bar		*next;
}							t_live_bar;

typedef struct				s_vdata
{
	WINDOW					*left_window;
	WINDOW					*right_window;
	WINDOW					*alert_window;
	WINDOW					*input_window;
	WINDOW					*authors;
	int						key;
	int						paused;
	unsigned long long		sec;
	t_scroll_name			*scrolling_names;
	t_scrolling_controls	*scrolling_controls;
	unsigned long long		time;

	int						total_champs;
	
	int						input_cycle;
	int						input_entered;
	int						input_index;
	char					input_line[10];
	int						input_paused;

	int						last_win_cols_size;
	int						last_win_lines_size;

	int						active_alert;

	t_live_bar				*live_bars;

	char					author_line[AUTHOR_LEN];
	char					adv_line[AUTHOR_LEN];
	int						author_adv_switch;
	int						author_time;

	int						first_run;


    t_uchar                 prev_map[MEM_SIZE];
	int		                prev_spot_map[MEM_SIZE];
}							t_vdata;
void	                    show_carries(t_vdata *vdata, t_session *game, t_carry *carries, t_champ *champs);
void    					show_right(t_vdata *vdata, t_session *game, t_champ *champs);
void						show_left(t_vdata *vdata, t_session *game, t_champ *champs);
void print_player_code(t_vdata *vdata, int y, int x, t_uchar *map, int *spot_map, int index, t_champ *champs);
int							visu_initializing(t_vdata *vdata, t_arg *arg, t_champ *champs);
void						set_champs_names_to_scrolling(t_vdata *vdata, t_champ *champs, int total_champs);
int							visu_finalizing		(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg);
int							visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs,t_arg *arg);
void						show_players(WINDOW *nbr_win, t_champ *champs, int *i);
void						playback_controls(t_vdata *vdata, t_session *game, t_champ *champs);
void						scrolling_controls(t_vdata *vdata, int x, int y);
void						scrolling_name(t_vdata *vdata, t_uchar *player_name, int x, int y);
void						scrolling_of_the_names(t_vdata *vdata);
void						scrolling_finalizing(t_vdata *vdata);
void						music_player();

int							get_total_champs(t_champ *champ);

void						custom_cycle(t_vdata *vdata, t_session *game, t_champ *champs);

void						show_alert_window(t_vdata *vdata, char *alert, char *options);
void						custom_input_window(t_vdata *vdata, t_session *game, t_champ *champs);
void						exit_window(t_vdata *vdata, t_session *game, t_champ *champs);
void						gameover_window(t_vdata *vdata, t_session *game, t_champ *champs);

void						terminal_size_listener(t_vdata *vdata, t_session *game, t_champ *champs);

void						live_bars_initializing(t_vdata *vdata, t_champ *champs, int x, int y);
void						refresh_live_bars(t_vdata *vdata, int rerender);
void						live_bars_finalizing(t_vdata *vdata);

void						author_line_initializing(t_vdata *vdata);
void						author_line_scrolling();

void						refresh_live_bars(t_vdata *vdata, int rerender);
void						live_bars_initializing(t_vdata *vdata, t_champ *champs, int x, int y);

void                        set_champs_for_visu(t_champ *champs, t_vdata *vdata);
int							get_color(t_champ *champs, int id);
void						disclaimer(t_vdata *vdata, t_session *game, t_champ *champs);
#endif
