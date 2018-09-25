/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_management_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:34:11 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:34:11 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	restore_last_line(t_vdata *vdata)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while (msg)
	{
		if (msg->next && msg->next->left_lines == msg->next->total_lines)
		{
			msg->left_lines++;
			break ;
		}
		msg = msg->next;
	}
}

void	subtract_lines(t_vdata *vdata, int lines_to_subtract)
{
	t_msg	*msg;

	msg = vdata->console.msgs;
	while (lines_to_subtract && msg)
	{
		if (msg->left_lines && lines_to_subtract)
		{
			msg->left_lines--;
			lines_to_subtract--;
			continue;
		}
		msg = msg->next;
	}
}

void	console_delete_msg(t_msg *msg)
{
	if (msg->next)
		console_delete_msg(msg->next);
	if (msg->allocated)
		ft_strdel(&msg->text);
	ft_memdel((void*)&msg);
}
