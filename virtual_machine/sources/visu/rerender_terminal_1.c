/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_size_changing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:26:04 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/25 19:26:04 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	rerender_input_cycle(t_vdata *vdata)
{
	wresize(vdata->input_window, 1, 12);
	mvwin(vdata->input_window, 6, 219);
	if (vdata->input_entered)
	{
		wattron(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->input_window, 0, 0, "%s", "_________");
		if (vdata->input_index)
			mvwprintw(vdata->input_window, 0, 0, "%s", vdata->input_line);
		wattroff(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		wrefresh(vdata->input_window);
	}
}

static void	rerender_left_and_right(
	t_vdata *vdata, t_session *game, t_champ *champs)
{
	wresize(vdata->left_window, 66, 195);
	wresize(vdata->right_window, 33, 49);
	mvwin(vdata->left_window, 2, 0);
	mvwin(vdata->right_window, 2, 195);
	box(vdata->left_window, 0, 0);
	box(vdata->right_window, 0, 0);
	show_left(vdata, game, champs);
	show_right(vdata, game, champs);
}

static void	rerender_alert_window(t_vdata *vdata)
{
	wresize(vdata->alert_window, 14, 59);
	mvwin(vdata->alert_window, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
	if (vdata->active_alert == CUSTOM_CYCLE)
		show_alert_window(vdata, "  Unfortunately, you can't go back in time!",
			"Press [Enter] to continue.");
	else if (vdata->active_alert == EXIT)
		show_alert_window(vdata, "      Are you sure you want to exit?",
			"[Y] Yes           No [N]");
	else if (vdata->active_alert == GAME_OVER)
		show_alert_window(vdata, "   Game is over, would you like to exit?",
			"[Y] Yes           No [N]");
	else if (vdata->active_alert == DISCLAIMER)
		show_alert_window(vdata, "  Are you over 18 years old to continue?",
			"[Y] Yes           No [N]");
}

static void	rerender_live_bars(t_vdata *vdata, int x, int y)
{
	t_live_bar	*bar;

	bar = vdata->live_bars;
	while (bar)
	{
		wresize(bar->window, 1, BAR_LEN + 11);
		mvwin(bar->window, (x += 2), y);
		bar = bar->next;
	}
	refresh_live_bars(vdata, TRUE);
}

void		terminal_size_listener(
	t_vdata *vdata, t_session *game, t_champ *champs)
{
	refresh();
	if (vdata->last_win_cols_size != COLS ||
		vdata->last_win_lines_size != LINES)
	{
		if (!vdata->console.opened)
			system("printf \'\033[8;78;245t\'");
		vdata->last_win_cols_size = COLS;
		vdata->last_win_lines_size = LINES;
		refresh();
		rerender_console_windows(vdata);
		rerender_left_and_right(vdata, game, champs);
		rerender_input_cycle(vdata);
		rerender_alert_window(vdata);
		rerender_scrolling_names(vdata);
		rerender_live_bars(vdata, 67, 33);
	}
}
