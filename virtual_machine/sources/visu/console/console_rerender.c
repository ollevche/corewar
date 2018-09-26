/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_rerender.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:13:42 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:13:42 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	rerender_console_clock(t_vdata *vdata)
{
	wresize(vdata->console.clock_window, 2, vdata->console.width + 2);
	mvwin(vdata->console.clock_window, 0, 246);
	box(vdata->console.clock_window, 0, 0);
	mvwprintw(vdata->console.clock_window, 1, 3, "| ");
	mvwprintw(vdata->console.clock_window, 1, vdata->console.width - 3, " |");
	mvwprintw(
		vdata->console.clock_window, 1, 4, "%*s", vdata->console.width - 6, "");
	console_clock_refresh(vdata);
}

static void	rerender_console_option_1(t_vdata *vdata)
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

static void	rerender_console_option_2(t_vdata *vdata)
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

static void	rerender_console(t_vdata *vdata)
{
	if (vdata->console.opened && COLS <= 316)
		rerender_console_option_1(vdata);
	else if (vdata->console.opened &&
		(COLS < vdata->last_win_cols_size || COLS > 316))
		rerender_console_option_2(vdata);
	if (vdata->console.opened)
	{
		reget_text_lines_duo_to_new_width(vdata);
		vdata->console.scroll_position = 0;
	}
	vdata->console.refresh = 1;
}

void		rerender_console_windows(t_vdata *vdata)
{
	if (vdata->console.opened)
	{
		rerender_console(vdata);
		rerender_console_clock(vdata);
		werase(vdata->console.controls_window);
		wresize(vdata->console.controls_window, 10, vdata->console.width + 2);
		mvwin(vdata->console.controls_window, 68, 246);
		box(vdata->console.controls_window, 0, ' ');
		wattron(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->console.controls_window, 0,
			(vdata->console.width / 2 - 8), "Console controls");
		wattroff(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
		console_controls_displaying(vdata);
	}
}
