/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_keys2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:14:55 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/21 21:14:55 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	console_navigation_keys(t_vdata *vdata)
{
	if (KEY(TOP) && vdata->console.msgs_lines >
		CONSOLE_INPUT_LINES && !vdata->console.stop_scrolling)
	{
		restore_lines(vdata, false);
		subtract_lines(vdata, vdata->console.msgs_lines - CONSOLE_INPUT_LINES);
		vdata->console.scroll_position = vdata->console.msgs_lines -
		CONSOLE_INPUT_LINES;
	}
	if (KEY(BOTTOM) && vdata->console.scroll_position)
		restore_lines(vdata, false);
	if (KEY(UP) && !vdata->console.stop_scrolling)
	{
		subtract_lines(vdata, 1);
		vdata->console.scroll_position++;
		vdata->console.refresh = 1;
	}
	if (KEY(DOWN) && vdata->console.scroll_position > 0)
	{
		restore_last_line(vdata);
		vdata->console.scroll_position--;
		vdata->console.refresh = 1;
	}
}

static void	console_opening(t_vdata *vdata)
{
	if (KEY(C) && !vdata->console.active)
	{
		if (vdata->console.opened)
		{
			vdata->console.active = 0;
			vdata->console.opened = 0;
			system("printf \'\033[8;78;245t\'");
		}
		else
		{
			vdata->console.opened = 1;
			system("printf \'\033[8;78;316t\'");
		}
	}
}

static void	console_activation(t_vdata *vdata)
{
	if (KEY(TILDE) && ERASE_KEY)
	{
		if (!vdata->console.active)
		{
			vdata->console.active = 1;
			wattron(vdata->console.box_window,
				COLOR_PAIR(1 + vdata->design * 10));
			box(vdata->console.box_window, 0, 0);
			wattroff(vdata->console.box_window,
				COLOR_PAIR(1 + vdata->design * 10));
			vdata->console.refresh = 1;
		}
		else
		{
			vdata->console.active = 0;
			box(vdata->console.box_window, 0, 0);
			vdata->console.refresh = 1;
		}
		console_controls_displaying(vdata);
		wrefresh(vdata->console.box_window);
	}
}

int			console_keys(t_vdata *vdata)
{
	console_opening(vdata);
	if (vdata->console.opened)
	{
		console_activation(vdata);
		console_navigation_keys(vdata);
	}
	if (vdata->console.active)
	{
		console_delete_keys(vdata);
		if (console_input_keys(vdata) != 0)
			return (-1);
		if (KEY(DELETE) || KEY(BACKSPACE) || KEY(LEFT) || KEY(RIGHT))
			restore_lines(vdata, true);
		if (!vdata->input_paused)
			ERASE_KEY;
	}
	return (0);
}
