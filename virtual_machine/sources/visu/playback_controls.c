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

static void		temp_get_key_number(t_vdata *vdata)
{
	WINDOW *temp;
	temp = newwin(3 , 33, 3, 3);
	mvwprintw(temp, 1, 1, "%d", vdata->key);
	wrefresh(temp);
}

static void		speed_controls(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (KEY(LEFT) && vdata->sec > 5)
	{
		if (vdata->sec == 200)
			vdata->sec -= 10;
		else if (vdata->sec == 300)
			vdata->sec -= 20;
		else if (vdata->sec > 300)
			vdata->sec -= 50;
		else if ((vdata->sec > 100 && vdata->sec < 300))
			vdata->sec -= (vdata->sec / 100) * 10;
		else
			vdata->sec -= 5;
		if (vdata->paused)
			show_right(vdata, game, champs);
	}
	if (KEY(RIGHT) && vdata->sec < 1000)
	{
		if ((vdata->sec >= 100 && vdata->sec < 300))
			vdata->sec += (vdata->sec / 100) * 10;
		else if (vdata->sec >= 300)
			vdata->sec += 50;
		else
			vdata->sec += 5;
		if (vdata->paused)
			show_right(vdata, game, champs);
	}
}

static void		key_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
	noecho();
	timeout(1000 / vdata->sec);
	vdata->key = getch();
	vdata->scrolling_controls->key = vdata->key;
	if (vdata->key == 'm' || vdata->key == 'M')
		music_player();
	custom_cycle(vdata, game, champs);
	exit_window(vdata, game, champs);
	speed_controls(vdata, game, champs);
	scrolling_of_the_names(vdata);
}

void	playback_controls(t_vdata *vdata, t_session *game, t_champ *champs)
{

	key_listener(vdata, game, champs);

	if (KEY(SPACE) && ERASE_KEY)
		vdata->paused = 1;
	if (vdata->paused == 1)
	{
		show_right(vdata, game, champs);
		while (!KEY(SPACE))		
			key_listener(vdata, game, champs);
		vdata->paused = (vdata->input_paused ? ((vdata->input_paused = 0) || 1) : 0);
	}
}
