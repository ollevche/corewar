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

void static	rerender_input_cycle(t_vdata *vdata)
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

void static rerender_left_and_right(t_vdata *vdata, t_session *game, t_champ *champs)
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

void static	rerender_alert_window(t_vdata *vdata)
{
	wresize(vdata->alert_window, 14, 59);
	mvwin(vdata->alert_window, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
	if (vdata->active_alert == CUSTOM_CYCLE)
		show_alert_window(vdata, "  Unfortunately, you can't go back in time!", "Press [Enter] to continue.");
	else if (vdata->active_alert == EXIT)
		show_alert_window(vdata, "      Are you sure you want to exit?", "[Y] Yes           No [N]");
	else if (vdata->active_alert == GAME_OVER)
		show_alert_window(vdata, "   Game is over, would you like to exit?", "[Y] Yes           No [N]");
	else if (vdata->active_alert == DISCLAIMER)
		show_alert_window(vdata, "  Are you over 18 years old to continue?", "[Y] Yes           No [N]");
}

void static temp_names(t_vdata *vdata, t_scroll_name *relative, int *y, int *player) //TODO temp method
{
	t_scroll_name *child;
	child = relative;

	if (relative->next)
		temp_names(vdata, relative->next, y, player);
	wresize(child->window, 1, MAX_NAME_LEN + 2 + 10);
	mvwin(child->window, *y, 2);
	wattron(child->window, COLOR_PAIR(*player + vdata->design * 10));
	mvwprintw(child->window, 0, 0, "Player %d: %s", *player, child->displayed_name);
	wattroff(child->window, COLOR_PAIR(*player + vdata->design * 10));
	wrefresh(child->window);
	*player += 1;
	*y += 2;
}

void static rerender_scrolling_names(t_vdata *vdata) //TODO Not finished
{
	int y = 69;
	int player = 1;
	temp_names(vdata, vdata->scrolling_names, &y, &player);

	if (vdata->scrolling_controls->seconds)
	{
		wresize(vdata->scrolling_controls->window, 6, 45);
		mvwprintw(vdata->scrolling_controls->window, 4, 2, "                            ");
		mvwprintw(vdata->scrolling_controls->window, 5, 2, "                            ");
		wborder(vdata->scrolling_controls->window, 1, 1, 1, 1, 1, 1, 1, 1);
		wrefresh(vdata->scrolling_controls->window);
		wresize(vdata->scrolling_controls->window, 6, 45);
		wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->scrolling_controls->window, 3, 22, "auto  ");
		wattroff(vdata->scrolling_controls->window, A_BOLD);
	}
	else
	{
		wresize(vdata->scrolling_controls->window, 8, 45);
		mvwprintw(vdata->scrolling_controls->window, 4, 2, "[<] Scroll manually to left");
		mvwprintw(vdata->scrolling_controls->window, 5, 2, "[>] Scroll manually to right");
		wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->scrolling_controls->window, 3, 22, "manual");
		mvwprintw(vdata->scrolling_controls->window, 4, 3, "<");
		mvwprintw(vdata->scrolling_controls->window, 5, 3, ">");
		wattroff(vdata->scrolling_controls->window, A_BOLD);
	}
	box(vdata->scrolling_controls->window, 0, ' ');
	mvwprintw(vdata->scrolling_controls->window, 2, 2, "[R] Scrolling direction: ");
	mvwprintw(vdata->scrolling_controls->window, 3, 2, "[P] Scrolling type:");
	wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->scrolling_controls->window, 0, 11, "Name scrolling controls");
	mvwprintw(vdata->scrolling_controls->window, 2, 3, "R");
	mvwprintw(vdata->scrolling_controls->window, 3, 3, "P");
	wattroff(vdata->scrolling_controls->window, A_BOLD);
	mvwin(vdata->scrolling_controls->window, 69, 197);
	wrefresh(vdata->scrolling_controls->window);

	wresize(vdata->authors, 2, 195);
	box(vdata->authors, 0 , 0);
	mvwprintw(vdata->authors, 1, 3, "| ");
	mvwprintw(vdata->authors, 1, 190, " |");
	wrefresh(vdata->authors);

	wresize(vdata->players_window, 245, 1);
	mvwin(vdata->players_window, 0, 244);
	players_line_refresh(vdata);
}

void static	rerender_live_bars(t_vdata *vdata, int x, int y)
{
	t_live_bar	*bar;

	bar = vdata->live_bars;
	while(bar)
	{
		wresize(bar->window, 1, BAR_LEN + 11);
		mvwin(bar->window, (x += 2), y);
		bar = bar->next;
	}
	refresh_live_bars(vdata, TRUE);
}

void static rerender_console_clock(t_vdata *vdata)
{
	wresize(vdata->console.clock_window, 2, vdata->console.width + 2);
	mvwin(vdata->console.clock_window, 0, 246);
	box(vdata->console.clock_window, 0, 0);
	mvwprintw(vdata->console.clock_window, 1, 3, "| ");
	mvwprintw(vdata->console.clock_window, 1, vdata->console.width - 3, " |");
	mvwprintw(vdata->console.clock_window, 1, 4, "%*s", vdata->console.width - 6, "");
	console_clock_refresh(vdata);
}

void static	rerender_console(t_vdata *vdata)
{

	if (vdata->console.opened && COLS <= 316)
	{
		system("printf \'\033[8;78;316t\'");
		vdata->console.width = 68;
		wresize(vdata->console.window, 64, 68);
		mvwin(vdata->console.window, 3, 247);

		wresize(vdata->console.box_window, 66, 70);
		mvwin(vdata->console.box_window, 2, 246);

		if (vdata->console.active)
		{
			wattron(vdata->console.box_window, COLOR_PAIR(1 + vdata->design * 10));
			box(vdata->console.box_window, 0, 0);
			wattroff(vdata->console.box_window, COLOR_PAIR(1 + vdata->design * 10));
		}
		else
			box(vdata->console.box_window, 0, 0);

		wrefresh(vdata->console.window);
		wrefresh(vdata->console.box_window);
	}
	else if (vdata->console.opened && (COLS < vdata->last_win_cols_size || COLS > 316))
	{
		vdata->console.width = COLS - 245 - 1 - 2;
		wresize(vdata->console.window, 64, vdata->console.width);
		mvwin(vdata->console.window, 3, 247);

		wresize(vdata->console.box_window, 66, vdata->console.width + 2);
		mvwin(vdata->console.box_window, 2, 246);

		if (vdata->console.active)
		{
			wattron(vdata->console.box_window, COLOR_PAIR(1 + vdata->design * 10));
			box(vdata->console.box_window, 0, 0);
			wattroff(vdata->console.box_window, COLOR_PAIR(1 + vdata->design * 10));
		}
		else
			box(vdata->console.box_window, 0, 0);

		wrefresh(vdata->console.window);

		wrefresh(vdata->console.box_window);
	}

	if (vdata->console.opened)
	{
		reget_text_lines_duo_to_new_width(vdata);
		vdata->console.scroll_position = 0;
	}
	vdata->console.refresh = 1;
}

void static	rerender_console_controls(t_vdata *vdata)
{
	werase(vdata->console.controls_window);
	wresize(vdata->console.controls_window, 10, vdata->console.width + 2);
	mvwin(vdata->console.controls_window, 68, 246);
	box(vdata->console.controls_window, 0, ' ');
	wattron(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->console.controls_window, 0, (vdata->console.width / 2 - 8), "Console controls");
	wattroff(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
	console_controls_displaying(vdata);
}

void static rerender_console_windows(t_vdata *vdata)
{
	if (vdata->console.opened)
	{
		rerender_console(vdata);
		rerender_console_clock(vdata);
		rerender_console_controls(vdata);
	}
}

void		terminal_size_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
	refresh();
	if (vdata->last_win_cols_size != COLS || vdata->last_win_lines_size != LINES)
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
