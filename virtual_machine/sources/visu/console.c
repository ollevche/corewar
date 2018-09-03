/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:34:27 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/30 16:34:28 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int static	get_text_lines(t_vdata *vdata, char *text)
{
	int text_lines;
	int text_length;

	text_lines = 0;
	text_length = ft_strlen(text) + PREFIX_LEN;
	while(text_length > 0)
	{
		text_length -= vdata->console.width;
		text_lines++;
	}
	while(*text)
		if(*text++ == '\n')
			text_lines++;
	return (text_lines);
}

void static get_carriage_lines(t_vdata *vdata, t_msg *msg)
{
	int		carriage_length;
	int		carriage_lines;

	msg->total_lines = get_text_lines(vdata, msg->text);
	msg->left_lines = msg->total_lines;
	carriage_length = vdata->console.carriage_index + 1 + PREFIX_LEN;
	carriage_lines = 0;
	while(carriage_length > 0)
	{
		carriage_length -= vdata->console.width;
		carriage_lines++;
	}	
	vdata->console.carriage_lines = carriage_lines;
}

void		reget_text_lines_duo_to_new_width(t_vdata *vdata)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while(msg)
	{	
		if (msg == vdata->console.msgs)
			get_carriage_lines(vdata, msg);
		else
		{			
			msg->total_lines = get_text_lines(vdata, msg->text);
			msg->left_lines = msg->total_lines;
		}		
		msg = msg->next;
	}
}

void static	restore_lines(t_vdata *vdata, int carriage)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while(msg)
	{
		if (carriage && msg == vdata->console.msgs)
			get_carriage_lines(vdata, msg);
		else
			msg->left_lines = msg->total_lines;
		msg = msg->next;
	}
	vdata->console.refresh = 1;
	vdata->console.scroll_position = 0;
}

void static	restore_last_line(t_vdata *vdata)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while(msg)
	{
		if (msg->next && msg->next->left_lines == msg->next->total_lines)
		{
			msg->left_lines++;
			break ;
		}
		msg = msg->next;
	}
}

void static subtract_lines(t_vdata *vdata, int lines_to_subtract)
{
	t_msg	*msg;
	
	msg = vdata->console.msgs;
	while(lines_to_subtract && msg)
	{
		if(msg->left_lines && lines_to_subtract)
		{
			msg->left_lines--;
			lines_to_subtract--;
			continue;
		}
		msg = msg->next;
	}
}

int static	get_total_text_lines(t_vdata *vdata)
{
	t_msg	*msg;
	int		total_lines;

	total_lines = 0;
	msg = vdata->console.msgs;
	while(msg)
	{
		total_lines += msg->total_lines;
		msg = msg->next;
	}
	return (total_lines);
}

void static console_navigation_keys(t_vdata *vdata)
{
	if (KEY(TOP) && vdata->console.msgs_lines > CONSOLE_INPUT_LINES && !vdata->console.stop_scrolling)
	{
		restore_lines(vdata, false);
		subtract_lines(vdata, vdata->console.msgs_lines - CONSOLE_INPUT_LINES);		
		vdata->console.scroll_position = vdata->console.msgs_lines - CONSOLE_INPUT_LINES;
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

void static console_delete_keys(t_vdata *vdata)
{
	if (KEY(DELETE))
		if (vdata->console.input_index > 1 && vdata->console.carriage_index + 1 < vdata->console.input_index)
		{
			ft_strcpy(vdata->console.input_line + vdata->console.carriage_index + 1, vdata->console.input_line + vdata->console.carriage_index + 2);
			vdata->console.input_index--;			
		}
	if (KEY(BACKSPACE))
	{
		if (vdata->console.carriage_index > 0 && vdata->console.carriage_index < vdata->console.input_index)
		{
			ft_strcpy(vdata->console.input_line + vdata->console.carriage_index - 1, vdata->console.input_line + vdata->console.carriage_index);
			vdata->console.input_index--;
			vdata->console.carriage_index--;
		}
		else if (vdata->console.carriage_index > 0 && vdata->console.carriage_index == vdata->console.input_index)
		{
			vdata->console.input_line[vdata->console.carriage_index--] = '\0';
			vdata->console.input_line[--vdata->console.input_index] = ' ';
		}
	}
}

void static	console_input_keys(t_vdata *vdata)
{
	if (KEY(LEFT))
		if (vdata->console.carriage_index > 0)
			vdata->console.carriage_index--;
	if (KEY(RIGHT))
		if (vdata->console.carriage_index < vdata->console.input_index)
			vdata->console.carriage_index++;
	if (vdata->console.input_index < (CONSOLE_INPUT_LEN - 2) && (vdata->key >= 32 && vdata->key <= 126))
	{
		if (vdata->console.carriage_index < vdata->console.input_index)
		{
			ft_memmove(vdata->console.input_line + vdata->console.carriage_index + 1, vdata->console.input_line + vdata->console.carriage_index, vdata->console.input_index - vdata->console.carriage_index);
			vdata->console.input_line[vdata->console.carriage_index] = vdata->key;
		}
		else
			vdata->console.input_line[vdata->console.input_index] = vdata->key;		
		if (vdata->console.input_index == vdata->console.carriage_index)
			vdata->console.carriage_index++;
		vdata->console.input_index++;
		vdata->console.input_line[vdata->console.input_index] = ' ';		
		restore_lines(vdata, true);
	}
}

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

void static	console_drawing(t_vdata *vdata)
{
	t_msg	*msg;
	int		y;

	y = (vdata->console.msgs_lines > CONSOLE_INPUT_LINES ? CONSOLE_INPUT_LINES : vdata->console.msgs_lines);
	msg = vdata->console.msgs;
	while(msg && (y -= msg->left_lines) >= 0)
	{
		console_drawing_logic(vdata, msg, y);
		msg = msg->next;
	}
	if (msg && msg->total_lines > 1 && y > -(msg->total_lines - 0) )
		mvwprintw(vdata->console.window, 0, 0, msg->text + vdata->console.width - PREFIX_LEN + vdata->console.width * (-y - 1));
	if ((vdata->console.msgs_lines > CONSOLE_INPUT_LINES && msg))
		vdata->console.stop_scrolling = 0;
	else
		vdata->console.stop_scrolling = 1;
}

int tempik = 1;

void console_delete_msg(t_msg *msg)
{
	if (msg->next)
		console_delete_msg(msg->next);
	if (msg->allocated)
		ft_strdel(&msg->text);
	ft_memdel((void*)&msg);
}

void static console_clear_command(t_vdata *vdata)
{
	if (vdata->console.msgs->next)
	{
		console_delete_msg(vdata->console.msgs->next);
		vdata->console.msgs->next = NULL;
		vdata->console.scroll_position = 0;
	}
}

void static console_help_command(t_vdata *vdata)
{
	char *message;

	message = "You can use these commands:\nclear\nexit";
	visu_print_static(vdata, message);
}

void static	console_commands(t_vdata *vdata)
{
	char *command = vdata->console.msgs->text;
	command[vdata->console.input_index] = '\0';
	if (!ft_strcmp(command, "exit"))
		exit(1);
	if (!ft_strcmp(command, "-help"))
		console_help_command(vdata);
	else if (!ft_strcmp(command, "clear"))
		console_clear_command(vdata);
	else
		visu_print_allocated(vdata, ft_strjoin("command not found: ", vdata->console.msgs->text));
}


void		console_refresh(t_vdata *vdata) //TODO
{	
	if (KEY(ENTER) && vdata->console.active)
	{	
		if (vdata->console.input_index)
			visu_print_allocated(vdata, ft_strdup(vdata->console.msgs->text));
		else
			visu_print_static(vdata, "");
		console_commands(vdata);
		vdata->console.carriage_index = 0;
		vdata->console.carriage_lines = 1;
		vdata->console.msgs->left_lines = 1;
		vdata->console.msgs->total_lines = 1;		
		vdata->console.input_index = 0;
		ft_bzero(vdata->console.msgs->text, CONSOLE_INPUT_LEN);
		vdata->console.msgs->text[0] = ' ';
		restore_lines(vdata, FALSE);
	}

	if (vdata->key == 'Q') // TEMP DEBUG
	{
		char *temp_char = ft_itoa(tempik++);
		visu_print_allocated(vdata, ft_strjoin("incoming text fdohgiodfhgildfjgiljdfligjldfkjgdjfklgjdflkgjlkdfjlkgjkdlfjgkjdfgjkldfjgkldfjkgdfjgdflkgjlkdfjglkdjflkgldfjgdfkjgfdg#", temp_char));
		ft_strdel(&temp_char);
	}
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


	if (KEY(TILDE) && vdata->console.opened && ERASE_KEY)
	{
		if (!vdata->console.active)
		{
			vdata->console.active = 1;
			wattron(vdata->console.box_window, COLOR_PAIR(1));
			box(vdata->console.box_window, 0, 0);
			wattroff(vdata->console.box_window, COLOR_PAIR(1));
			vdata->console.refresh = 1;
		}
		else
		{
			vdata->console.active = 0;
			box(vdata->console.box_window, 0, 0);
			vdata->console.refresh = 1;			
		}
		wrefresh(vdata->console.box_window);		
	}
	if (vdata->console.opened)
		console_navigation_keys(vdata);
	if (vdata->console.active)
	{
		console_delete_keys(vdata);
		console_input_keys(vdata);
		if (KEY(DELETE) || KEY(BACKSPACE) || KEY(LEFT) || KEY(RIGHT))
			restore_lines(vdata, true);
		ERASE_KEY;	
	}
	if (vdata->console.refresh)
	{
		vdata->console.refresh = 0;
		werase(vdata->console.window);
		vdata->console.msgs_lines = get_total_text_lines(vdata) + 0;
		console_drawing(vdata);
		wrefresh(vdata->console.window);
	}
}

void static	visu_print(t_vdata *vdata, char *text, char allocated)
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

void		visu_print_static(t_vdata *vdata, char *text)
{
	visu_print(vdata, text, 0);
}

void		visu_print_allocated(t_vdata *vdata, char *text)
{
	visu_print(vdata, text, 'Y');
}

t_msg static	*create_console_input(t_vdata *vdata)
{
	t_msg *input_line;

	input_line = (t_msg*)ft_memalloc(sizeof(t_msg));
	ft_strcpy(input_line->prefix, "Corewar:");
	input_line->total_lines = 1;
	input_line->left_lines = 1;	
	ft_bzero(vdata->console.input_line, CONSOLE_INPUT_LEN);
	input_line->text = vdata->console.input_line;
	input_line->text[0] = ' ';
	return (input_line);
}

void static		console_clock_initializing(t_vdata *vdata)
{
	box(vdata->console.clock_window, 0, 0);
	mvwprintw(vdata->console.clock_window, 1, 3, "| ");
	mvwprintw(vdata->console.clock_window, 1, 65, " |");
	mvwprintw(vdata->console.clock_window, 1, 4, "%62s", "");
	wrefresh(vdata->console.clock_window);
}

void			console_clock_refresh(t_vdata *vdata)
{
	struct tm		*ptm;
	struct timeval	tv;

	if (vdata->console.opened && ((tv.tv_sec) - vdata->console.clock_time) >= 1)
	{
		gettimeofday(&tv, NULL);
		ptm = localtime (&tv.tv_sec);
		strftime(vdata->console.clock, sizeof(vdata->console.clock), "%Y-%m-%d %H:%M:%S", ptm);
		mvwprintw(vdata->console.clock_window, 1, vdata->console.width / 2 - 9, vdata->console.clock);
		wrefresh(vdata->console.clock_window);
		vdata->console.clock_time = (tv.tv_sec);
	}
}

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

void		console_initializing(t_vdata *vdata)
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
}

void		console_finalizing(t_vdata *vdata)
{
	console_delete_msg(vdata->console.msgs);
	delwin(vdata->console.window);
	delwin(vdata->console.box_window);
	delwin(vdata->console.clock_window);
	delwin(vdata->console.controls_window);
}