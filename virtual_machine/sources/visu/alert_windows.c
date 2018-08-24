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

void		show_alert_window(t_vdata *vdata, char *alert, char *options)
{
	werase(vdata->alert_window);
	wattron(vdata->alert_window, COLOR_PAIR(141) | A_BOLD);
	mvwprintw(vdata->alert_window, 9, 8, "%s", alert);
	mvwprintw(vdata->alert_window, 11, 17, "%s", options);
	box(vdata->alert_window, 0, 0);
	wattroff(vdata->alert_window, COLOR_PAIR(141) | A_BOLD);			
	wrefresh(vdata->alert_window);
}

void			exit_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (KEY(ESC) && ERASE_KEY)
	{
		if (!vdata->paused)
		{
			mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");	
			wrefresh(vdata->right_window);
		}
		show_alert_window(vdata, "      Are you sure you want to exit?", "[Y] Yes           No [N]");
		while (!(KEY(Y) || KEY(N) || KEY(ESC)))
		{
			scrolling_of_the_names(vdata);
			vdata->key = getch();
		}
		if (KEY(Y))
		{
			scrolling_finalizing(vdata);
			delwin(vdata->left_window);
			delwin(vdata->right_window);
			delwin(vdata->alert_window);
			delwin(vdata->input_window);
			endwin();
			exit(1); // TODO
		}
		if (vdata->paused)
			show_left(vdata, game, champs);
	}
}

void			custom_input_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (!vdata->paused)
	{
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");	
		wrefresh(vdata->right_window);
	}
	show_alert_window(vdata, "  Unfortunately, you can't go back in time!", "Press [Enter] to continue.");
	while (!(KEY(ENTER) || KEY(ESC)))
	{
		scrolling_of_the_names(vdata);
		vdata->key = getch();
	}
	if (ERASE_KEY && vdata->paused)
		show_left(vdata, game, champs);
}

void			gameover_window(t_vdata *vdata, t_session *game, t_champ *champs)
{
	vdata->paused = 1;
	show_left(vdata, game, champs);
	show_right(vdata, game, champs);
	mvwprintw(vdata->right_window, 1, START_X, "%s", "** GAME IS OVER **");	
	wrefresh(vdata->right_window);
	show_alert_window(vdata, "   Game is over, would you like to exit?", "[Y] Yes           No [N]");
	while (!(KEY(Y) || KEY(N) || KEY(ESC)))
	{
		scrolling_of_the_names(vdata);
		vdata->key = getch();
	}
	if (KEY(Y))
	{
		scrolling_finalizing(vdata);
		delwin(vdata->left_window);
		delwin(vdata->right_window);
		delwin(vdata->alert_window);
		delwin(vdata->input_window);
		endwin();
		exit(1); // TODO
	}
	if (KEY(N))
	{
		show_left(vdata, game, champs);
		while(69)
		{
			scrolling_of_the_names(vdata);
			exit_window(vdata, game, champs);
			vdata->key = getch();
			vdata->scrolling_controls->key = vdata->key;
		}
	}

	show_left(vdata, game, champs);
}