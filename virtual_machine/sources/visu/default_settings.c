/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:59:43 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/21 19:59:43 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	get_total_champs(t_champ *champ)
{
	int players;

	players = 0;
	while (champ && (champ = champ->next))
		players++;
	return (++players);
}

static void	set_champs_for_visu(t_champ *champs, t_vdata *vdata)
{
	int y;

	y = 69;
	init_design(0, vdata->total_champs);
	while (champs != NULL)
	{
		scrolling_name(vdata, champs->name, y, 2);
		champs = champs->next;
		y += 2;
	}
}

static void	settings_1st_stage(t_vdata *vdata)
{
	vdata->left_window = newwin(66, 195, 2, 0);
	vdata->right_window = newwin(33, 49, 2, 195);
	vdata->alert_window = newwin(14, 59, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
	vdata->input_window = newwin(1, 12, 6, 219);
	vdata->players_window = newwin(245, 1, 0, 244);
	vdata->key = 0;
	vdata->paused = 1;
	vdata->sec = 5;
	vdata->scrolling_names = NULL;
	vdata->scrolling_controls = NULL;
	vdata->time = 0;
	vdata->input_cycle = 0;
	vdata->input_entered = 0;
	vdata->input_index = 0;
	ft_bzero(vdata->input_line, 10);
	vdata->input_paused = 0;
}

static void	settings_2nd_stage(t_vdata *vdata, t_champ *champs)
{
	vdata->total_champs = get_total_champs(champs);
	vdata->last_win_cols_size = COLS;
	vdata->last_win_lines_size = LINES;
	vdata->active_alert = 0;
	vdata->live_bars = NULL;
	vdata->author_adv_switch = 1;
	vdata->author_time = 0;
	vdata->first_run = 1;
	ft_bzero(vdata->prev_map, sizeof(t_uchar) * MEM_SIZE);
	ft_bzero(vdata->prev_spot_map, sizeof(int) * MEM_SIZE);
	ft_bzero(vdata->color_map_div, sizeof(long long) * 4);
	vdata->design = 0;
	ft_bzero(vdata->set_design, sizeof(bool) * 3);
	vdata->music = 0;
}

void		default_settings(
	t_vdata *vdata, t_arg *arg, t_champ *champs, t_session *game)
{
	settings_1st_stage(vdata);
	settings_2nd_stage(vdata, champs);
	vdata->arg = arg;
	vdata->champs = champs;
	vdata->game = game;
	set_escdelay(0);
	keypad(stdscr, TRUE);
	curs_set(0);
	refresh();
	start_color();
	set_champs_for_visu(champs, vdata);
	init_design(vdata->design, vdata->total_champs);
	box(vdata->left_window, 0, 0);
	box(vdata->right_window, 0, 0);
	if (COLS != W_WIDTH || LINES != W_HEIGHT)
		system("printf \'\033[8;78;245t\'");
}
