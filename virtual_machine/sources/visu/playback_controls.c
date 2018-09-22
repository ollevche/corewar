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

static void	speed_controls(t_vdata *vdata, t_session *game, t_champ *champs)
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
	}
	if (KEY(RIGHT) && vdata->sec < 1000)
	{
		if ((vdata->sec >= 100 && vdata->sec < 300))
			vdata->sec += (vdata->sec / 100) * 10;
		else if (vdata->sec >= 300)
			vdata->sec += 50;
		else
			vdata->sec += 5;
	}
	if (vdata->paused && (KEY(RIGHT) || KEY(LEFT)))
		show_right(vdata, game, champs);
}

static void	one_step_forward(t_vdata *vdata)
{
	if (KEY(S))
	{
		if (vdata->paused)
		{
			vdata->key = 32;
			vdata->input_paused = 1;
		}
		else
			vdata->paused = 1;
	}
}

static void	music(t_vdata *vdata)
{
	if (KEY(M))
		music_player();
}

static int	key_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
	terminal_size_listener(vdata, game, champs);
	noecho();
	timeout(1000 / vdata->sec);
	vdata->key = getch();
	if (disclaimer_window(vdata, game, champs) != 0)
		return (-1);
	console_clock_refresh(vdata);
	if (console_refresh(vdata) != 0)
		return (-1);
	vdata->scrolling_controls->key = vdata->key;
	music(vdata);
	if (change_design(vdata, game, champs) != 0)
		return (-1);
	custom_cycle(vdata, game, champs);
	one_step_forward(vdata);
	if (exit_window(vdata, game, champs) != 0)
		return (-1);
	speed_controls(vdata, game, champs);
	scrolling_of_the_names(vdata);
	return (0);
}

int			playback_controls(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (key_listener(vdata, game, champs) != 0)
		return (-1);
	if (KEY(SPACE) && ERASE_KEY)
		vdata->paused = 1;
	if (vdata->paused == 1)
	{
		show_right(vdata, game, champs);
		while (!KEY(SPACE))
		{
			if (key_listener(vdata, game, champs) != 0)
				return (-1);
		}
	}
	if (vdata->input_paused)
	{
		vdata->input_paused = 0;
		vdata->paused = 1;
	}
	else
		vdata->paused = 0;
	return (0);
}
