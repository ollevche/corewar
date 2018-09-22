/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert_windows2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:54:40 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/21 21:54:41 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	gameover_window_option(
	t_vdata *vdata, t_session *game, t_champ *champs)
{
	vdata->paused = 1;
	show_left(vdata, game, champs);
	show_right(vdata, game, champs);
	mvwprintw(vdata->right_window, 1, START_X, "%s", "** GAME IS OVER **");
	wrefresh(vdata->right_window);
	show_alert_window(vdata, "   Game is over, would you like to exit?",
		"[Y] Yes           No [N]");
	vdata->active_alert = GAME_OVER;
}

int			gameover_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	gameover_window_option(vdata, game, champs);
	while (!(KEY(Y) || KEY(N) || KEY(ESC)))
	{
		terminal_size_listener(vdata, game, champs);
		scrolling_of_the_names(vdata);
		vdata->key = getch();
	}
	if (KEY(Y))
	{
		visu_finalizing(vdata, vdata->arg);
		return (-1);
	}
	vdata->active_alert = 0;
	show_left(vdata, game, champs);
	while (69)
	{
		terminal_size_listener(vdata, game, champs);
		scrolling_of_the_names(vdata);
		if (exit_window(vdata, game, champs) != 0)
			return (-1);
		vdata->key = getch();
		vdata->scrolling_controls->key = vdata->key;
	}
	return (0);
}
