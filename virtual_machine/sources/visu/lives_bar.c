/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lives_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:29:02 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/26 18:29:03 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"


void static	render_live_bar(t_live_bar *bar, int fill_size, int player, int design)
{
	int i;

	ft_bzero(bar->line, BAR_LEN);
	i = 0;
	while(i < BAR_LEN - 1 && i < fill_size)
		bar->line[i++] = ' ';
	if (!bar->line[0])
		bar->line[0] = ' ';
	werase(bar->window);
	// (void)player;
	// (void)design;
	wattron(bar->window, COLOR_PAIR(player + design * 10) | A_REVERSE);
	mvwprintw(bar->window, 0, 0, "%s", bar->line);
	wattroff(bar->window, COLOR_PAIR(player + design * 10) | A_REVERSE);
	wattron(bar->window, COLOR_PAIR(player + design * 10));
	mvwprintw(bar->window, 0, ft_strlen(bar->line) + 1, "%d", *bar->lives);
	wattroff(bar->window, COLOR_PAIR(player + design * 10));
	wrefresh(bar->window);
}

void static	calculate_ratio(t_live_bar *bar, int biggest, int player, int rerender, int design)
{
	int fill_size;
	int ratio;

	if (bar->lives)
	{
		if (biggest == *bar->lives)
			fill_size = BAR_LEN - 1;
		else
		{
			ratio = *bar->lives * 100 / biggest;
			fill_size = (BAR_LEN - 1) * ratio / 100;
		}
		if (rerender || (bar->prev_line != fill_size || bar->prev_lives != *bar->lives))
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
	t_live_bar	*bar;

	if (player > vdata->total_champs)
	{
		player = 1;
		biggest = 0;
	}
	bar = vdata->live_bars;
	while(bar)
	{
		if (biggest < *bar->lives)
			biggest = *bar->lives;
		bar = bar->next;
	}
	bar = vdata->live_bars;
	while(bar)
	{
		calculate_ratio(bar, biggest, player, rerender, vdata->design);
		bar = bar->next;
		player++;
	}
}

void static	create_live_bar(t_vdata *vdata, t_champ *champs, int x, int y)
{
	static int	player = 1;
	t_live_bar	*bar;
	t_live_bar	*temp_bar;
	t_champ		*champ;

	bar = (t_live_bar*)ft_memalloc(sizeof(t_live_bar));
	bar->window = newwin(1, BAR_LEN + 11, x, y);
	bar->prev_lives = -1;
	bar->prev_line = -1;
	ft_bzero(bar->line, BAR_LEN);
	champ = champs;
	(void)temp_bar;
	(void)vdata;
	while (champ)
	{
		if (get_color(champs, champ->id) == player)
			bar->lives = &champ->period_lives;
		champ = champ->next;
	}
	if (vdata->live_bars)
	{
		temp_bar = vdata->live_bars;
		while(temp_bar->next)
			temp_bar = temp_bar->next;
		temp_bar->next = bar;
	}
	else
		vdata->live_bars = bar;
	player++;
}

void		live_bars_initializing(t_vdata *vdata, t_champ *champs, int x, int y)
{
	int player;

	player = 0;
	while (player < vdata->total_champs)
	{
		create_live_bar(vdata, champs, (x += 2), y);
		player++;
	}
}

void		live_bars_finalizing(t_vdata *vdata)
{
	t_live_bar *bar;

	bar = vdata->live_bars;
	while (bar)
	{
		delwin(bar->window);
		bar = bar->next;
	}
}