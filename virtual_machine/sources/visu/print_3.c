/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 22:36:59 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 22:36:59 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int	change_design(t_vdata *vdata, t_session *game, t_champ *champs)
{
	t_console *tmp_console;

	tmp_console = &vdata->console;
	if (KEY('d') || KEY('D'))
	{
		vdata->design = (vdata->design + 2) % (4 * 2);
		if (vdata->set_design[vdata->design / 2] == 0)
		{
			init_design(vdata->design, vdata->total_champs);
			vdata->set_design[vdata->design / 2] = 1;
		}
		tmp_console->refresh = 1;
		if (console_refresh(vdata) != 0)
			return (-1);
		refresh_scroll_names(vdata);
		players_line_refresh(vdata);
		show_left(vdata, game, champs);
		show_right(vdata, game, champs);
		refresh_live_bars(vdata, TRUE);
		wrefresh(vdata->scrolling_names->window);
	}
	return (0);
}

int	get_color(t_champ *champs, int id)
{
	int i;

	i = 1;
	while (champs != NULL)
	{
		if (champs->id == id)
			return (i);
		i++;
		champs = champs->next;
	}
	return (0);
}
