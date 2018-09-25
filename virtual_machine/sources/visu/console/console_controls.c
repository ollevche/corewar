/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:28:00 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:28:00 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	console_bold_activated(t_vdata *vdata, int y, WINDOW *window)
{
	wattron(window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(window, 0, (vdata->console.width / 2 - 8), "Console controls");
	mvwprintw(window, ++y, 3, "~");
	wattron(window, COLOR_PAIR(2));
	mvwprintw(window, y, 23, "activated");
	wattroff(window, COLOR_PAIR(2));
	mvwprintw(window, ++y, 3, "Left");
	mvwprintw(window, y, 14, "Right");
	mvwprintw(window, ++y, 3, "Up");
	mvwprintw(window, y, 12, "Down");
	mvwprintw(window, ++y, 3, "Backspace");
	mvwprintw(window, ++y, 3, "Delete");
	mvwprintw(window, ++y, 3, "Enter");
	mvwprintw(window, ++y, 3, "Page Up");
	mvwprintw(window, y, 16, "Page Down");
	wattroff(window, COLOR_PAIR(GRAY) | A_BOLD);
}

static void	console_bold_deactivated(t_vdata *vdata, int y, WINDOW *window)
{
	wattron(window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(window, 0, (vdata->console.width / 2 - 8), "Console controls");
	mvwprintw(window, ++y, 3, "~");
	wattron(window, COLOR_PAIR(1));
	mvwprintw(window, y, 23, "deactivated");
	wattroff(window, COLOR_PAIR(1));
	mvwprintw(window, ++y, 3, "Up");
	mvwprintw(window, y, 12, "Down");
	mvwprintw(window, ++y, 3, "Page Up");
	mvwprintw(window, y, 16, "Page Down");
	wattroff(window, COLOR_PAIR(GRAY) | A_BOLD);
}

static void	console_activated(int y, WINDOW *window)
{
	mvwprintw(window, ++y, 2, "[~] Corewar console: activated");
	mvwprintw(window, ++y, 2, "[Left] and [Right] arrows move the cursor");
	mvwprintw(window, ++y, 2, "[Up] and [Down] arrows scroll the output");
	mvwprintw(window, ++y, 2,
		"[Backspace] deletes a character backward of the cursor");
	mvwprintw(window, ++y, 2,
		"[Delete] deletes a character forward of the cursor");
	mvwprintw(window, ++y, 2, "[Enter] takes the input");
	mvwprintw(window, ++y, 2,
		"[Page Up] or [Page Down] scroll to the top or to the bottom");
}

static void	console_deactivated(int y, WINDOW *window)
{
	mvwprintw(window, ++y, 2, "[~] Corewar console: deactivated");
	mvwprintw(window, ++y, 2, "[Up] and [Down] arrows scroll the output");
	mvwprintw(window, ++y, 2,
		"[Page Up] or [Page Down] scroll to the top or to the bottom");
}

void		console_controls_displaying(t_vdata *vdata)
{
	werase(vdata->console.controls_window);
	box(vdata->console.controls_window, 0, ' ');
	if (vdata->console.active)
	{
		console_activated(1, vdata->console.controls_window);
		console_bold_activated(vdata, 1, vdata->console.controls_window);
	}
	else
	{
		console_deactivated(1, vdata->console.controls_window);
		console_bold_deactivated(vdata, 1, vdata->console.controls_window);
	}
	wrefresh(vdata->console.controls_window);
}
