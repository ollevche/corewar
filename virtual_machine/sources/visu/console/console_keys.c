/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:14:10 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:14:10 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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
	if (KEY(ENTER))
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
}

void static	console_opening(t_vdata *vdata)
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

void static	console_activation(t_vdata *vdata)
{
	if (KEY(TILDE) && ERASE_KEY)
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
}

int tempik = 1; //////////////////////////////////////////////
void	console_keys(t_vdata *vdata)
{
	if (vdata->key == 'Q') // TEMP DEBUG
	{
		char *temp_char = ft_itoa(tempik++);
		visu_print_allocated(vdata, ft_strjoin("incoming text #", temp_char));
		ft_strdel(&temp_char);
	}
	console_opening(vdata);
	if (vdata->console.opened)
	{
		console_activation(vdata);
		console_navigation_keys(vdata);
	}
	if (vdata->console.active)
	{
		console_delete_keys(vdata);
		console_input_keys(vdata);
		if (KEY(DELETE) || KEY(BACKSPACE) || KEY(LEFT) || KEY(RIGHT))
			restore_lines(vdata, true);
		ERASE_KEY;	
	}
}
