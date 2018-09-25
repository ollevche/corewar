/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerender_terminal_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 20:17:40 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 20:17:40 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	rerender_scrolling_names_option1(
	t_vdata *vdata, t_scroll_name *relative, int *y, int *player)
{
	t_scroll_name *child;

	child = relative;
	if (relative->next)
		rerender_scrolling_names_option1(vdata, relative->next, y, player);
	wresize(child->window, 1, MAX_NAME_LEN + 2 + 10);
	mvwin(child->window, *y, 2);
	wattron(child->window, COLOR_PAIR(*player + vdata->design * 10));
	mvwprintw(child->window, 0, 0,
		"Player %d: %s", *player, child->displayed_name);
	wattroff(child->window, COLOR_PAIR(*player + vdata->design * 10));
	wrefresh(child->window);
	*player += 1;
	*y += 2;
}

static void	rerender_scrolling_names_option2(t_vdata *vdata)
{
	wresize(vdata->scrolling_controls->window, 6, 45);
	mvwprintw(vdata->scrolling_controls->window,
		4, 2, "                            ");
	mvwprintw(vdata->scrolling_controls->window,
		5, 2, "                            ");
	wborder(vdata->scrolling_controls->window, 1, 1, 1, 1, 1, 1, 1, 1);
	wrefresh(vdata->scrolling_controls->window);
	wresize(vdata->scrolling_controls->window, 6, 45);
	wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->scrolling_controls->window, 3, 22, "auto  ");
	wattroff(vdata->scrolling_controls->window, A_BOLD);
}

static void	rerender_scrolling_names_option3(t_vdata *vdata)
{
	wresize(vdata->scrolling_controls->window, 8, 45);
	mvwprintw(vdata->scrolling_controls->window,
		4, 2, "[<] Scroll manually to left");
	mvwprintw(vdata->scrolling_controls->window,
		5, 2, "[>] Scroll manually to right");
	wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->scrolling_controls->window, 3, 22, "manual");
	mvwprintw(vdata->scrolling_controls->window, 4, 3, "<");
	mvwprintw(vdata->scrolling_controls->window, 5, 3, ">");
	wattroff(vdata->scrolling_controls->window, A_BOLD);
}

static void	rerender_scrolling_names_option4(t_vdata *vdata)
{
	box(vdata->scrolling_controls->window, 0, ' ');
	mvwprintw(vdata->scrolling_controls->window,
		2, 2, "[R] Scrolling direction: ");
	mvwprintw(vdata->scrolling_controls->window,
		3, 2, "[P] Scrolling type:");
	wattron(vdata->scrolling_controls->window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->scrolling_controls->window,
		0, 11, "Name scrolling controls");
	mvwprintw(vdata->scrolling_controls->window, 2, 3, "R");
	mvwprintw(vdata->scrolling_controls->window, 3, 3, "P");
	wattroff(vdata->scrolling_controls->window, A_BOLD);
	mvwin(vdata->scrolling_controls->window, 69, 197);
	wrefresh(vdata->scrolling_controls->window);
	wresize(vdata->authors, 2, 195);
	box(vdata->authors, 0, 0);
	mvwprintw(vdata->authors, 1, 3, "| ");
	mvwprintw(vdata->authors, 1, 190, " |");
	wrefresh(vdata->authors);
	wresize(vdata->players_window, 245, 1);
	mvwin(vdata->players_window, 0, 244);
}

void		rerender_scrolling_names(t_vdata *vdata)
{
	int y;
	int player;

	y = 69;
	player = 1;
	rerender_scrolling_names_option1(vdata,
		vdata->scrolling_names, &y, &player);
	if (vdata->scrolling_controls->seconds)
		rerender_scrolling_names_option2(vdata);
	else
		rerender_scrolling_names_option3(vdata);
	rerender_scrolling_names_option4(vdata);
	players_line_refresh(vdata);
}
