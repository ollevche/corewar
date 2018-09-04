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

void static console_bold_activated(t_vdata *vdata, int y)
{
	wattron(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->console.controls_window, 0, (vdata->console.width / 2 - 8), "Console controls");
	mvwprintw(vdata->console.controls_window, ++y, 3, "~");
	wattron(vdata->console.controls_window, COLOR_PAIR(2));	
	mvwprintw(vdata->console.controls_window, y, 23, "activated");
	wattroff(vdata->console.controls_window, COLOR_PAIR(2));
	mvwprintw(vdata->console.controls_window, ++y, 3, "Left");	
	mvwprintw(vdata->console.controls_window, y, 14, "Right");
	mvwprintw(vdata->console.controls_window, ++y, 3, "Up");	
	mvwprintw(vdata->console.controls_window, y, 12, "Down");
	mvwprintw(vdata->console.controls_window, ++y, 3, "Backspace");
	mvwprintw(vdata->console.controls_window, ++y, 3, "Delete");
	mvwprintw(vdata->console.controls_window, ++y, 3, "Enter");	
	mvwprintw(vdata->console.controls_window, ++y, 3, "Page Up");	
	mvwprintw(vdata->console.controls_window, y, 16, "Page Down");	
	wattroff(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);	
}

void static console_bold_deactivated(t_vdata *vdata, int y)
{
	wattron(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->console.controls_window, 0, (vdata->console.width / 2 - 8), "Console controls");
	mvwprintw(vdata->console.controls_window, ++y, 3, "~");
	wattron(vdata->console.controls_window, COLOR_PAIR(1));	
	mvwprintw(vdata->console.controls_window, y, 23, "deactivated");
	wattroff(vdata->console.controls_window, COLOR_PAIR(1));
	mvwprintw(vdata->console.controls_window, ++y, 3, "Up");	
	mvwprintw(vdata->console.controls_window, y, 12, "Down");
	mvwprintw(vdata->console.controls_window, ++y, 3, "Page Up");	
	mvwprintw(vdata->console.controls_window, y, 16, "Page Down");
	wattroff(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
}

void		console_controls_displaying(t_vdata *vdata)
{	
	int y;

	y = 1;
	werase(vdata->console.controls_window);
	box(vdata->console.controls_window, 0, ' ');	
	if (vdata->console.active)
	{
		mvwprintw(vdata->console.controls_window, ++y, 2, "[~] Corewar console: activated");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Left] and [Right] arrows move the cursor");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Up] and [Down] arrows scroll the output");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Backspace] deletes a character backward of the cursor");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Delete] deletes a character forward of the cursor");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Enter] takes the input");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Page Up] or [Page Down] scroll to the top or to the bottom");
		console_bold_activated(vdata, 1);
	}
	else
	{
		mvwprintw(vdata->console.controls_window, ++y, 2, "[~] Corewar console: deactivated");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Up] and [Down] arrows scroll the output");
		mvwprintw(vdata->console.controls_window, ++y, 2, "[Page Up] or [Page Down] scroll to the top or to the bottom");
		console_bold_deactivated(vdata, 1);
	}
	wrefresh(vdata->console.controls_window);
}
