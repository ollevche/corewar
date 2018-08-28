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
	wresize(vdata->right_window, 20, 49);
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
}		

void static temp_names(t_scroll_name *relative, int *y, int *player) //TODO temp method
{
	t_scroll_name *child;
	child = relative;

	if (relative->next)
		temp_names(relative->next, y, player);
	wresize(child->window, 1, MAX_NAME_LEN + 2 + 10);
	mvwin(child->window, *y, 2);
	wattron(child->window, COLOR_PAIR(*player));
	mvwprintw(child->window, 0, 0, "Player %d: %s", *player, child->displayed_name);	
	wattroff(child->window, COLOR_PAIR(*player));
	wrefresh(child->window);
	*player += 1;
	*y += 2;
}

void static rerender_scrolling_names(t_vdata *vdata) //TODO Not finished
{
	int y = 67;
	int player = 1;
	temp_names(vdata->scrolling_names, &y, &player);

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
	mvwin(vdata->scrolling_controls->window, 67, 197);
	wrefresh(vdata->scrolling_controls->window);
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

void		terminal_size_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
	refresh();
	if (vdata->last_win_cols_size != COLS || vdata->last_win_lines_size != LINES)
	{
		system("printf \'\033[8;76;244t\'");
		vdata->last_win_cols_size = COLS;
		vdata->last_win_lines_size = LINES;	
		refresh();
		rerender_left_and_right(vdata, game, champs);
		rerender_input_cycle(vdata);
		rerender_alert_window(vdata);
		rerender_scrolling_names(vdata);
		rerender_live_bars(vdata, 65, 33);
	}
}
