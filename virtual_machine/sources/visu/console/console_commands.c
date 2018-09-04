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

int static console_cycle_command(t_vdata *vdata, char *command) //TODO
{
	char	*line;


	if (vdata->console.input_index <= 15 && (line = ft_strchr(command, ' ')))
	{
		vdata->input_cycle = ft_atoi(line + 1);
		if (vdata->paused && vdata->input_cycle > vdata->game->cycle)
		{
			vdata->key = 32;
			vdata->input_paused = 1;
		}
		else if (vdata->input_cycle < vdata->game->cycle)
		{
			vdata->input_cycle = 0;
			custom_input_window(vdata, vdata->game, vdata->champs);
		}
	}
	else
		visu_print_static(vdata, "usage: cycle [up to 9-digit number]");

	return (1);
}

void		console_commands(t_vdata *vdata)
{
	char *command = vdata->console.msgs->text;
	if (!vdata->console.input_index)
		return ;
	else if (!ft_strncmp(command, "exit", 4))
	{
		vdata->key = ESC;
		exit_window(vdata, vdata->game, vdata->champs);
	}
	else if (!ft_strncmp(command, "-help", 5))
		console_help_command(vdata);
	else if (!ft_strncmp(command, "clear", 5))
		console_clear_command(vdata);
	else if (!ft_strncmp(command, "cycle", 5))
		console_cycle_command(vdata, command);
	
	else
		visu_print_allocated(vdata, ft_strjoin("command not found: ", vdata->console.msgs->text));
}
