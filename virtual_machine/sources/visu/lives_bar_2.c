/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lives_bar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 22:11:05 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/21 22:11:05 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	render_live_bar(
	t_live_bar *bar, int fill_size, int player, int design)
{
	int i;

	ft_bzero(bar->line, BAR_LEN);
	i = 0;
	while (i < BAR_LEN - 1 && i < fill_size)
		bar->line[i++] = ' ';
	if (!bar->line[0])
		bar->line[0] = ' ';
	werase(bar->window);
	wattron(bar->window, COLOR_PAIR(player + design * 10) | A_REVERSE);
	mvwprintw(bar->window, 0, 0, "%s", bar->line);
	wattroff(bar->window, COLOR_PAIR(player + design * 10) | A_REVERSE);
	wattron(bar->window, COLOR_PAIR(player + design * 10));
	mvwprintw(bar->window, 0, ft_strlen(bar->line) + 1, "%d", *bar->lives);
	wattroff(bar->window, COLOR_PAIR(player + design * 10));
	wrefresh(bar->window);
}

static void	calculate_ratio(
	t_live_bar *bar, int biggest, int player, int sucks[])
{
	int fill_size;
	int ratio;
	int rerender;
	int design;

	rerender = sucks[0];
	design = sucks[1];
	if (bar->lives)
	{
		if (biggest == *bar->lives)
			fill_size = BAR_LEN - 1;
		else
		{
			ratio = *bar->lives * 100 / biggest;
			fill_size = (BAR_LEN - 1) * ratio / 100;
		}
		if (rerender || (bar->prev_line != fill_size ||
			bar->prev_lives != *bar->lives))
		{
			bar->prev_line = fill_size;
			bar->prev_lives = *bar->lives;
			render_live_bar(bar, fill_size, player, design);
		}
	}
}

void		refresh_live_bars(t_vdata *vdata, int rerender)
{
	static int	player = 1;
	static int	biggest = 0;
	int			sucks[2];
	t_live_bar	*bar;

	if (player > vdata->total_champs && (player = 1))
		biggest = 0;
	bar = vdata->live_bars;
	while (bar)
	{
		if (biggest < *bar->lives)
			biggest = *bar->lives;
		bar = bar->next;
	}
	bar = vdata->live_bars;
	while (bar)
	{
		sucks[0] = rerender;
		sucks[1] = vdata->design;
		calculate_ratio(bar, biggest, player, sucks);
		bar = bar->next;
		player++;
	}
}
