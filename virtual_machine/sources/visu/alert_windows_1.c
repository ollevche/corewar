/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert_windows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:35:21 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/23 17:35:21 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	show_alert_window(t_vdata *vdata, char *alert, char *options)
{
	werase(vdata->alert_window);
	wattron(vdata->alert_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->alert_window, 9, 8, "%s", alert);
	mvwprintw(vdata->alert_window, 11, 17, "%s", options);
	box(vdata->alert_window, 0, 0);
	wattroff(vdata->alert_window, COLOR_PAIR(GRAY) | A_BOLD);
	wrefresh(vdata->alert_window);
}

int		exit_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (KEY(ESC) && ERASE_KEY)
	{
		if (!vdata->paused)
		{
			mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");
			wrefresh(vdata->right_window);
		}
		show_alert_window(vdata, "      Are you sure you want to exit?",
			"[Y] Yes           No [N]");
		vdata->active_alert = EXIT;
		while (!(KEY(Y) || KEY(N) || KEY(ESC)))
		{
			terminal_size_listener(vdata, game, champs);
			scrolling_of_the_names(vdata);
			vdata->key = getch();
		}
		if (!(vdata->active_alert = 0) && KEY(Y))
		{
			visu_finalizing(vdata, vdata->arg);
			return (-1);
		}
		if (vdata->paused)
			show_left(vdata, game, champs);
	}
	return (0);
}

void	custom_input_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	ERASE_KEY;
	if (!vdata->paused)
	{
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");
		wrefresh(vdata->right_window);
	}
	show_alert_window(vdata, "  Unfortunately, you can't go back in time!",
		"Press [Enter] to continue.");
	vdata->active_alert = CUSTOM_CYCLE;
	while (!(KEY(ENTER) || KEY(ESC)))
	{
		terminal_size_listener(vdata, game, champs);
		scrolling_of_the_names(vdata);
		vdata->key = getch();
	}
	if (ERASE_KEY && vdata->paused)
		show_left(vdata, game, champs);
	vdata->active_alert = 0;
}

int		disclaimer_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (vdata->first_run)
	{
		vdata->first_run = 0;
		show_alert_window(vdata, "  Are you over 18 years old to continue?",
			"[Y] Yes           No [N]");
		vdata->active_alert = DISCLAIMER;
		while (!(KEY(Y) || KEY(N)))
		{
			terminal_size_listener(vdata, game, champs);
			scrolling_of_the_names(vdata);
			vdata->key = getch();
		}
		vdata->active_alert = 0;
		if (KEY(N))
		{
			visu_finalizing(vdata, vdata->arg);
			return (-1);
		}
		show_left(vdata, game, champs);
		ERASE_KEY;
	}
	return (0);
}
