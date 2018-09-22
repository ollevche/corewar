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

static void	key_backspace(t_vdata *vdata)
{
	if (KEY(BACKSPACE))
	{
		if (vdata->console.carriage_index > 0 &&
			vdata->console.carriage_index < vdata->console.input_index)
		{
			ft_strcpy(vdata->console.input_line + vdata->console.carriage_index
				- 1, vdata->console.input_line + vdata->console.carriage_index);
			vdata->console.input_index--;
			vdata->console.carriage_index--;
		}
		else if (vdata->console.carriage_index > 0 &&
			vdata->console.carriage_index == vdata->console.input_index)
		{
			vdata->console.input_line[vdata->console.carriage_index--] = '\0';
			vdata->console.input_line[--vdata->console.input_index] = ' ';
		}
	}
}

void		console_delete_keys(t_vdata *vdata)
{
	if (KEY(DELETE))
	{
		if (vdata->console.input_index > 1 && vdata->console.carriage_index
			+ 1 < vdata->console.input_index)
		{
			ft_strcpy(vdata->console.input_line + vdata->console.carriage_index
				+ 1, vdata->console.input_line +
				vdata->console.carriage_index + 2);
			vdata->console.input_index--;
		}
	}
	key_backspace(vdata);
}

static void	key_left_and_right(t_vdata *vdata)
{
	if (KEY(LEFT))
		if (vdata->console.carriage_index > 0)
			vdata->console.carriage_index--;
	if (KEY(RIGHT))
		if (vdata->console.carriage_index < vdata->console.input_index)
			vdata->console.carriage_index++;
}

static int	key_enter(t_vdata *vdata)
{
	if (KEY(ENTER))
	{
		if (vdata->console.input_index)
			visu_print_allocated(vdata, ft_strdup(vdata->console.msgs->text));
		else
			visu_print_static(vdata, "");
		if (console_commands(vdata) != 0)
			return (-1);
		vdata->console.carriage_index = 0;
		vdata->console.carriage_lines = 1;
		vdata->console.msgs->left_lines = 1;
		vdata->console.msgs->total_lines = 1;
		vdata->console.input_index = 0;
		ft_bzero(vdata->console.msgs->text, CONSOLE_INPUT_LEN);
		vdata->console.msgs->text[0] = ' ';
		restore_lines(vdata, FALSE);
	}
	return (0);
}

int			console_input_keys(t_vdata *vdata)
{
	key_left_and_right(vdata);
	if (vdata->console.input_index < (CONSOLE_INPUT_LEN - 2) &&
		(vdata->key >= 32 && vdata->key <= 126))
	{
		if (vdata->console.carriage_index < vdata->console.input_index)
		{
			ft_memmove(vdata->console.input_line + vdata->console.carriage_index
				+ 1, vdata->console.input_line + vdata->console.carriage_index,
				vdata->console.input_index - vdata->console.carriage_index);
			vdata->console.input_line[vdata->console.carriage_index] =
			vdata->key;
		}
		else
			vdata->console.input_line[vdata->console.input_index] = vdata->key;
		if (vdata->console.input_index == vdata->console.carriage_index)
			vdata->console.carriage_index++;
		vdata->console.input_index++;
		vdata->console.input_line[vdata->console.input_index] = ' ';
		restore_lines(vdata, true);
	}
	return (key_enter(vdata));
}
