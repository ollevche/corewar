/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_management_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:13:26 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:13:26 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			get_text_lines(t_vdata *vdata, char *text)
{
	int text_lines;
	int text_length;

	text_lines = 0;
	text_length = ft_strlen(text) + PREFIX_LEN;
	while (text_length > 0)
	{
		text_length -= vdata->console.width;
		text_lines++;
	}
	return (text_lines);
}

static void	get_carriage_lines(t_vdata *vdata, t_msg *msg)
{
	int		carriage_length;
	int		carriage_lines;

	msg->total_lines = get_text_lines(vdata, msg->text);
	msg->left_lines = msg->total_lines;
	carriage_length = vdata->console.carriage_index + 1 + PREFIX_LEN;
	carriage_lines = 0;
	while (carriage_length > 0)
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
	while (msg)
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

void		restore_lines(t_vdata *vdata, int carriage)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while (msg)
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

int			get_total_text_lines(t_vdata *vdata)
{
	t_msg	*msg;
	int		total_lines;

	total_lines = 0;
	msg = vdata->console.msgs;
	while (msg)
	{
		total_lines += msg->total_lines;
		msg = msg->next;
	}
	return (total_lines);
}
