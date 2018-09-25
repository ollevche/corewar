/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrolling_names.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 00:28:31 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/21 00:28:32 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	pause_key_listener_option1(t_vdata *vdata, WINDOW *window)
{
	vdata->scrolling_controls->seconds = 0;
	wresize(window, 8, 45);
	box(window, 0, ' ');
	mvwprintw(window, 4, 2, "[<] Scroll manually to left");
	mvwprintw(window, 5, 2, "[>] Scroll manually to right");
	wattron(window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(window, 0, 11, "Name scrolling controls");
	mvwprintw(window, 3, 22, "manual");
	mvwprintw(window, 4, 3, "<");
	mvwprintw(window, 5, 3, ">");
	wattroff(window, A_BOLD);
}

static void	pause_key_listener_option2(t_vdata *vdata, WINDOW *window)
{
	vdata->scrolling_controls->seconds = 150;
	mvwprintw(window, 4, 2, "                            ");
	mvwprintw(window, 5, 2, "                            ");
	wborder(window, 1, 1, 1, 1, 1, 1, 1, 1);
	wrefresh(window);
	wresize(window, 6, 45);
	box(window, 0, ' ');
	wattron(window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(window, 0, 11, "Name scrolling controls");
	mvwprintw(window, 3, 22, "auto  ");
	wattroff(window, A_BOLD);
}

static void	pause_key_listener(t_vdata *vdata)
{
	if (vdata->scrolling_controls->key == 112)
	{
		if (vdata->scrolling_controls->seconds)
			pause_key_listener_option1(
				vdata, vdata->scrolling_controls->window);
		else
			pause_key_listener_option2(
				vdata, vdata->scrolling_controls->window);
		wrefresh(vdata->scrolling_controls->window);
	}
}

static void	scrolling_of_the_names_helper(t_vdata *vdata)
{
	int				color;
	t_scroll_name	*name;

	color = vdata->total_champs;
	if (vdata->scrolling_controls->seconds)
	{
		name = vdata->scrolling_names;
		while (name)
		{
			if (vdata->scrolling_controls->direction)
				scroll_to_left(name, color, vdata->design);
			else
				scroll_to_right(name, color, vdata->design);
			name = name->next;
			color--;
		}
	}
}

void		scrolling_of_the_names(t_vdata *vdata)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (((time.tv_sec) - vdata->author_time) >= 5)
	{
		vdata->author_adv_switch = (vdata->author_adv_switch ? 0 : 1);
		vdata->author_time = (time.tv_sec);
	}
	if (((time.tv_usec / 1000) - vdata->time) >=
		(vdata->scrolling_controls->seconds ? 150 : 150))
	{
		author_line_scrolling(vdata);
		scrolling_of_the_names_helper(vdata);
		vdata->time = (time.tv_usec / 1000);
	}
	direction_key_listener(vdata->scrolling_controls);
	pause_key_listener(vdata);
	scroll_manually_keys_listener(vdata->scrolling_controls,
		vdata->scrolling_names, vdata->total_champs, vdata->design);
}
