/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_lifecycle_methods.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:25:26 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:25:26 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	visu_print_static(t_vdata *vdata, char *text)
{
	visu_print(vdata, text, 0);
}

void	visu_print_allocated(t_vdata *vdata, char *text)
{
	visu_print(vdata, text, 'Y');
}

void	console_initializing(t_vdata *vdata)
{
	vdata->console.window = newwin(64, 68, 3, 247);
	vdata->console.box_window = newwin(66, 70, 2, 246);
	vdata->console.clock_window = newwin(2, 70, 0, 246);
	vdata->console.controls_window = newwin(10, 70, 68, 246);
	vdata->console.msgs = create_console_input(vdata);
	vdata->console.msgs_lines = 0;
	vdata->console.input_index = 0;
	vdata->console.carriage_index = 0;
	vdata->console.carriage_lines = 1;
	vdata->console.scroll_position = 0;
	vdata->console.stop_scrolling = 1;
	vdata->console.refresh = 1;
	vdata->console.opened = 0;
	vdata->console.active = 0;
	vdata->console.width = 68;
	vdata->console.clock_time = 0;
	console_clock_initializing(vdata);
	visu_print_static(vdata, "Welcome to Corewar console!");
	visu_print_static(vdata, "See the available commands by typing -help");
}

int		console_refresh(t_vdata *vdata)
{
	if (console_keys(vdata) != 0)
		return (-1);
	if (vdata->console.refresh)
	{
		vdata->console.refresh = 0;
		werase(vdata->console.window);
		vdata->console.msgs_lines = get_total_text_lines(vdata) + 0;
		console_drawing(vdata);
		wrefresh(vdata->console.window);
	}
	return (0);
}

void	console_finalizing(t_vdata *vdata)
{
	console_delete_msg(vdata->console.msgs);
	delwin(vdata->console.window);
	delwin(vdata->console.box_window);
	delwin(vdata->console.clock_window);
	delwin(vdata->console.controls_window);
}
