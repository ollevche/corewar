/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:15:27 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/23 17:15:27 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	backspace_listener(t_vdata *vdata)
{
	if (KEY(BACKSPACE) && vdata->input_entered && vdata->input_index > 0)
	{
		vdata->input_line[--vdata->input_index] = '\0';
		werase(vdata->input_window);
		wattron(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->input_window, 0, 0, "%s", "_________");
		mvwprintw(vdata->input_window, 0, 0, "%s", vdata->input_line);
		wattroff(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		wrefresh(vdata->input_window);
	}
}

static void	number_listener(t_vdata *vdata)
{
	if (KEY('0') && !vdata->input_index)
		return ;
	if (NUMBER_KEYS && vdata->input_entered && vdata->input_index < 9)
	{
		vdata->input_line[vdata->input_index++] = vdata->key;
		wattron(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->input_window, 0, 0, "%s", vdata->input_line);
		wattroff(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		wrefresh(vdata->input_window);
	}
}

static void	input_entering_listener(t_vdata *vdata)
{
	if (KEY(E))
	{
		if (vdata->input_entered)
		{
			ft_bzero(vdata->input_line, 10);
			vdata->input_index = 0;
			werase(vdata->input_window);
			wrefresh(vdata->input_window);
		}
		else
		{
			wattron(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
			mvwprintw(vdata->input_window, 0, 0, "%s", "_________");
			wattroff(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
			wrefresh(vdata->input_window);
		}
		vdata->input_entered = (vdata->input_entered ? 0 : 1);
	}
}

static void	enter_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
	if (KEY(ENTER) && vdata->input_entered && ERASE_KEY)
	{
		vdata->input_cycle = ft_atoi(vdata->input_line);
		ft_bzero(vdata->input_line, 10);
		vdata->input_index = 0;
		werase(vdata->input_window);
		wrefresh(vdata->input_window);
		vdata->input_entered = (vdata->input_entered ? 0 : 1);
		if (vdata->input_cycle <= 0)
			return ;
		if (vdata->paused && vdata->input_cycle > game->cycle)
		{
			vdata->key = 32;
			vdata->input_paused = 1;
		}
		else if (vdata->input_cycle < game->cycle)
		{
			vdata->input_cycle = 0;
			custom_input_window(vdata, game, champs);
		}
	}
}

void		custom_cycle(t_vdata *vdata, t_session *game, t_champ *champs)
{
	backspace_listener(vdata);
	number_listener(vdata);
	input_entering_listener(vdata);
	enter_listener(vdata, game, champs);
}
