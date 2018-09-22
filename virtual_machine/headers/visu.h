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

#ifndef VISU_H
# define VISU_H
# include <ncurses.h>
# include <unistd.h>
# include <stdbool.h>
# include "vm.h"
# include <sys/time.h>
# define LEFT_D 1
# define RIGHT_D 0
# define MAX_NAME_LEN 20
# define W_HEIGHT 78
# define W_WIDTH 245
# define START_X 2
# define N_DESIGNS 4
# define GRAY 0
# define GRAY_B 1234
# define PLAYER_1 1
# define PLAYER_2 2
# define PLAYER_3 3
# define PLAYER_4 4
# define NEW_PLAYER_1 5
# define NEW_PLAYER_2 6
# define NEW_PLAYER_3 7
# define NEW_PLAYER_4 8
# define COLOR_JA 4181
# define ESC 27
# define LEFT 260
# define RIGHT 261
# define ENTER '\n'
# define E 101
# define Y 121
# define N 110
# define S 115
# define M 109
# define TILDE 96
# define SPACE 32
# define BACKSPACE 127
# define DELETE 330
# define NUMBER_KEYS (vdata->key >= '0' && vdata->key <= '9')
# define KEY(x) (vdata->key == x)
# define ERASE_KEY (vdata->key = -1)
# define UP 259
# define DOWN 258
# define BOTTOM 338
# define TOP 339
# define C 99
# define CUSTOM_CYCLE 1
# define GAME_OVER 2
# define EXIT 3
# define DISCLAIMER 4
# define ACTIVE_ALERT(x) x == CUSTOM_CYCLE || x == GAME_OVER || x == GAME_OVER
# define BAR_LEN 150
# define AUTHOR_LEN 186
# define PREFIX_LEN 9
# define CONSOLE_INPUT_LEN 1000
# define CONSOLE_INPUT_LINES 64

typedef struct				s_scrolling_controls
{
	WINDOW					*window;
	int						direction;
	int						key;
	unsigned long long		seconds;
}							t_scrolling_controls;

typedef struct				s_scroll_name
{
	WINDOW					*window;
	char					*full_name;
	int						full_name_len;
	char					*displayed_name;
	char					*hidden_name;
	int						hidden_len;
	struct s_scroll_name	*next;
}							t_scroll_name;

typedef struct				s_live_bar
{
	WINDOW					*window;
	char					line[BAR_LEN];
	int						*lives;
	int						prev_lives;
	int						prev_line;
	struct s_live_bar		*next;
}							t_live_bar;

typedef struct				s_msg
{
	char					*text;
	char					allocated;
	int						left_lines;
	int						total_lines;
	char					prefix[PREFIX_LEN];
	struct s_msg			*next;
}							t_msg;

typedef struct				s_console
{
	WINDOW					*window;
	WINDOW					*box_window;
	WINDOW					*clock_window;
	WINDOW					*controls_window;
	t_msg					*msgs;
	int						msgs_lines;
	char					input_line[CONSOLE_INPUT_LEN];
	int						input_index;
	int						carriage_index;
	int						carriage_lines;
	int						scroll_position;
	int						stop_scrolling;
	int						refresh;
	int						opened;
	int						active;
	int						width;
	char					clock[20];
	int						clock_time;
}							t_console;

typedef struct				s_vdata
{
	WINDOW					*left_window;
	WINDOW					*right_window;
	WINDOW					*alert_window;
	WINDOW					*input_window;
	WINDOW					*authors;
	WINDOW					*players_window;
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
	t_uchar					prev_map[MEM_SIZE];
	int						prev_spot_map[MEM_SIZE];
	long long int			color_map_div[4];
	t_console				console;
	int						design;
	bool					set_design[N_DESIGNS];
	t_arg					*arg;
	t_champ					*champs;
	t_session				*game;
	bool					music;
}							t_vdata;

void						show_right(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						show_left(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						set_champs_names_to_scrolling(
	t_vdata *vdata, t_champ *champs, int total_champs);
int							visu_finalizing(t_vdata *vdata, t_arg *arg);
int							visualizing(
	t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg);
void						show_players(
	WINDOW *nbr_win, t_champ *champs, int *i);
int							playback_controls(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						scrolling_controls(t_vdata *vdata, int x, int y);
void						scrolling_name(
	t_vdata *vdata, t_uchar *player_name, int x, int y);
void						scrolling_of_the_names(t_vdata *vdata);
void						scrolling_finalizing(t_vdata *vdata);
void						music_player();
void						custom_cycle(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						show_alert_window(
	t_vdata *vdata, char *alert, char *options);
void						custom_input_window(
	t_vdata *vdata, t_session *game, t_champ *champs);
int							exit_window(
	t_vdata *vdata, t_session *game, t_champ *champs);
int							gameover_window(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						terminal_size_listener(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						live_bars_initializing(
	t_vdata *vdata, t_champ *champs, int x, int y);
void						refresh_live_bars(t_vdata *vdata, int rerender);
void						live_bars_finalizing(t_vdata *vdata);
void						author_line_initializing(t_vdata *vdata);
void						author_line_scrolling();
void						refresh_live_bars(t_vdata *vdata, int rerender);
void						live_bars_initializing(
	t_vdata *vdata, t_champ *champs, int x, int y);
int							get_color(t_champ *champs, int id);
int							disclaimer_window(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						players_line_refresh(t_vdata *vdata);
void						visu_print_static(t_vdata *vdata, char *text);
void						visu_print_allocated(t_vdata *vdata, char *text);
void						console_initializing(t_vdata *vdata);
void						console_finalizing(t_vdata *vdata);
int							console_refresh(t_vdata *vdata);
void						reget_text_lines_duo_to_new_width(t_vdata *vdata);
void						console_clock_initializing(t_vdata *vdata);
void						console_clock_refresh(t_vdata *vdata);
void						console_controls_displaying(t_vdata *vdata);
int							change_design(
	t_vdata *vdata, t_session *game, t_champ *champs);
void						init_design(int design, int total_champs);
void						refresh_scroll_names(t_vdata *vdata);
int							console_commands(t_vdata *vdata);
void						console_drawing(t_vdata *vdata);
int							console_keys(t_vdata *vdata);
int							get_text_lines(t_vdata *vdata, char *text);
void						restore_lines(t_vdata *vdata, int carriage);
void						subtract_lines(
	t_vdata *vdata, int lines_to_subtract);
void						restore_last_line(t_vdata *vdata);
int							get_total_text_lines(t_vdata *vdata);
t_msg						*create_console_input(t_vdata *vdata);
void						visu_print(
	t_vdata *vdata, char *text, char allocated);
void						console_delete_msg(t_msg *msg);
void						default_settings(
	t_vdata *vdata, t_arg *arg, t_champ *champs, t_session *game);
void						console_delete_keys(t_vdata *vdata);
int							console_input_keys(t_vdata *vdata);
void						rerender_console_windows(t_vdata *vdata);
void						scroll_manually_keys_listener(
	t_scrolling_controls *sc, t_scroll_name
	*scrolling_names, int total_champs, int design);
void						direction_key_listener(t_scrolling_controls *sc);
void						scroll_to_left(
	t_scroll_name *name, int color, int design);
void						scroll_to_right(
	t_scroll_name *name, int color, int design);
void						rerender_scrolling_names(t_vdata *vdata);
#endif
