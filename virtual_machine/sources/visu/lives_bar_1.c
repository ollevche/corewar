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

static int	*get_champ_period_lives(t_champ *champs, int player)
{
	t_champ *champ;

	champ = champs;
	while (champ)
	{
		if (get_color(champs, champ->id) == player)
			return (&champ->period_lives);
		champ = champ->next;
	}
	return (NULL);
}

static void	create_live_bar(t_vdata *vdata, t_champ *champs, int x, int y)
{
	static int	player = 1;
	t_live_bar	*bar;
	t_live_bar	*temp_bar;

	bar = (t_live_bar*)ft_memalloc(sizeof(t_live_bar));
	bar->window = newwin(1, BAR_LEN + 11, x, y);
	bar->prev_lives = -1;
	bar->prev_line = -1;
	ft_bzero(bar->line, BAR_LEN);
	bar->lives = get_champ_period_lives(champs, player);
	if (vdata->live_bars)
	{
		temp_bar = vdata->live_bars;
		while (temp_bar->next)
			temp_bar = temp_bar->next;
		temp_bar->next = bar;
	}
	else
		vdata->live_bars = bar;
	player++;
}

void		live_bars_initializing(
	t_vdata *vdata, t_champ *champs, int x, int y)
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
		free(bar);
		bar = bar->next;
	}
}
