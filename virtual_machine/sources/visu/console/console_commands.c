/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:34:36 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 19:34:37 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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

void		console_commands(t_vdata *vdata)
{
	char *command = vdata->console.msgs->text;
	command[vdata->console.input_index] = '\0';
	if (!vdata->console.input_index)
		return ;
	else if (!ft_strcmp(command, "exit"))
		exit(1);
	else if (!ft_strcmp(command, "-help"))
		console_help_command(vdata);
	else if (!ft_strcmp(command, "clear"))
		console_clear_command(vdata);
	else
		visu_print_allocated(vdata, ft_strjoin("command not found: ", vdata->console.msgs->text));
}
