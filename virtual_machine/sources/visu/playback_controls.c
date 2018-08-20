/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playback_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:35:44 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/19 14:35:45 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		key_listener(t_vdata *vdata)
{
	vdata->key = getch();
	if (vdata->key == KEY_LEFT && vdata->sec >= 5)
		vdata->sec -= vdata->sec > 5 ? 5 : 4;
	if (vdata->key == KEY_RIGHT && vdata->sec < 500)
		vdata->sec += vdata->sec == 1 ? 4 : 5;
	if (vdata->key > 0)
	{
		mvwprintw(vdata->right_window, 3, START_X, "Cycles/second:\t%d     ", vdata->sec);
		wrefresh(vdata->right_window);
	}
}

void	playback_controls(t_vdata *vdata)
{
	noecho();
	if (vdata->paused == 1)
	{
		vdata->paused = 0;
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");			
		wrefresh(vdata->right_window);
		while (vdata->key != 32)				
			key_listener(vdata);

	}
	if (vdata->paused == 0)
	{
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** RUNNING **");			
		wrefresh(vdata->right_window);
	}	
	timeout(1000 / vdata->sec);
	halfdelay(0);
	key_listener(vdata);
	if (vdata->key == 32)
	{		
		vdata->paused = 1;
		vdata->key = 0;
	}
}
