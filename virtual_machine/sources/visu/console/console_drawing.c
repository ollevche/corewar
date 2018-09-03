/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:14:41 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:14:41 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void static	console_drawing_logic(t_vdata *vdata, t_msg	*msg, int incoming_y)
{
	int y;
	int x;
	int precision;

	if (msg->left_lines)
	{
		y = incoming_y;
		x = 0;
		if (msg->left_lines > 1)
			precision = ((msg->left_lines - 1) * vdata->console.width + vdata->console.width) - PREFIX_LEN;
		else
			precision = vdata->console.width - PREFIX_LEN;
		mvwprintw(vdata->console.window, y, x, "%s %.*s", msg->prefix, precision, msg->text);

		wattron(vdata->console.window, COLOR_PAIR(1));
		mvwprintw(vdata->console.window, y, x, "%s", msg->prefix);
		wattroff(vdata->console.window, COLOR_PAIR(1));
	}
	if (msg == vdata->console.msgs && msg->left_lines >= vdata->console.carriage_lines)
	{
		y = (incoming_y + vdata->console.carriage_lines - 1);
		x = (vdata->console.carriage_index - (vdata->console.carriage_lines - 1) * vdata->console.width) + PREFIX_LEN;
		wattron(vdata->console.window, COLOR_PAIR(10) | A_BOLD);
		mvwprintw(vdata->console.window, y, x, "%.1s", &vdata->console.input_line[vdata->console.carriage_index]);
		wattroff(vdata->console.window, COLOR_PAIR(10) | A_BOLD);
	}
}

void		console_drawing(t_vdata *vdata)
{
	t_msg	*msg;
	int		y;
	char	*paragraph;

	y = (vdata->console.msgs_lines > CONSOLE_INPUT_LINES ? CONSOLE_INPUT_LINES : vdata->console.msgs_lines);
	msg = vdata->console.msgs;
	while(msg && (y -= msg->left_lines) >= 0)
	{
		console_drawing_logic(vdata, msg, y);
		msg = msg->next;
	}
	if (msg && msg->total_lines > 1 && y > -(msg->total_lines - 0) )
	{
		if ((paragraph = ft_strchr(msg->text, '\n')))
		{
			while(-y && (paragraph = ft_strchr(paragraph, '\n') + 1))
				y++;
			mvwprintw(vdata->console.window, 0, 0, paragraph);
		}
		else
			mvwprintw(vdata->console.window, 0, 0, msg->text + vdata->console.width - PREFIX_LEN + vdata->console.width * (-y - 1));
	}
	if ((vdata->console.msgs_lines > CONSOLE_INPUT_LINES && msg))
		vdata->console.stop_scrolling = 0;
	else
		vdata->console.stop_scrolling = 1;
}

void		visu_print(t_vdata *vdata, char *text, char allocated)
{
	t_msg			*new_msg;
	struct tm*		ptm;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);	
	new_msg = (t_msg*)ft_memalloc(sizeof(t_msg));	
	strftime(new_msg->prefix, 8, "%H:%M:%S", ptm);
	new_msg->total_lines = get_text_lines(vdata, text);
	new_msg->text = text;
	new_msg->allocated = allocated;
	if (vdata->console.scroll_position && (!vdata->console.msgs->left_lines))
		vdata->console.scroll_position++;
	else
		new_msg->left_lines = new_msg->total_lines;
	if (!vdata->console.msgs->next)
		vdata->console.msgs->next = new_msg;
	else
	{
		new_msg->next = vdata->console.msgs->next;
		vdata->console.msgs->next = new_msg;
	}
	vdata->console.refresh = 1;	
}
