/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_clock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:27:48 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:27:49 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	console_clock_initializing(t_vdata *vdata)
{
	box(vdata->console.clock_window, 0, 0);
	mvwprintw(vdata->console.clock_window, 1, 3, "| ");
	mvwprintw(vdata->console.clock_window, 1, 65, " |");
	mvwprintw(vdata->console.clock_window, 1, 4, "%62s", "");
	wrefresh(vdata->console.clock_window);
}

void	console_clock_refresh(t_vdata *vdata)
{
	struct tm		*ptm;
	struct timeval	tv;

	if (vdata->console.opened && ((tv.tv_sec) - vdata->console.clock_time) >= 1)
	{
		gettimeofday(&tv, NULL);
		ptm = localtime(&tv.tv_sec);
		strftime(vdata->console.clock,
			sizeof(vdata->console.clock), "%Y-%m-%d %H:%M:%S", ptm);
		mvwprintw(vdata->console.clock_window, 1,
			vdata->console.width / 2 - 9, vdata->console.clock);
		wrefresh(vdata->console.clock_window);
		vdata->console.clock_time = (tv.tv_sec);
	}
}
