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

void		console_controls_displaying(t_vdata *vdata) //TODO
{	
	int y;

	y = 1;
	mvwprintw(vdata->console.controls_window, y, 2, "DEBUG: [Shift]+[Q] Adds a test line. Console width is RESIZABLE!");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[~] Activates\\Deactivates the console");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Left] and [Right] arrows move the cursor");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Up] and [Down] arrows scroll the output");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Backspace] deletes a character backward of the cursor");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Delete] deletes a character forward of the cursor");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Enter] takes the input (NO COMMANDS YET)");
	mvwprintw(vdata->console.controls_window, ++y, 2, "[Page Up] or [Page Down] keys scroll to the top or the bottom");
	//mvwprintw(vdata->console.controls_window, ++y, 2, "* Console will not be closed before deactivating");
	y = 1;
	wattron(vdata->console.controls_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->console.controls_window, y, 2, "DEBUG");
	mvwprintw(vdata->console.controls_window, ++y, 3, "~");
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
	wrefresh(vdata->console.controls_window);
}
