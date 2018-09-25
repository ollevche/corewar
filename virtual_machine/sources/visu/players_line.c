/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:34:31 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/29 22:34:32 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	width_patch(t_vdata *vdata, int *ratio, int total_ratio)
{
	int player;

	player = 0;
	while (total_ratio < W_HEIGHT)
	{
		if (player > vdata->total_champs - 1)
			player = 0;
		ratio[player] += 1;
		player++;
		total_ratio++;
	}
}

static void	calculate_ratio(t_vdata *vdata, int *ratio, int ratio_sum)
{
	int player;
	int total_ratio;

	total_ratio = 0;
	player = 0;
	while (player < vdata->total_champs)
	{
		ratio[player] =
		((vdata->color_map_div[player] * 100 / ratio_sum) * W_HEIGHT) / 100;
		if (ratio[player] < 1 && vdata->color_map_div[player])
			ratio[player] += 1;
		total_ratio += ratio[player];
		player++;
	}
	width_patch(vdata, ratio, total_ratio);
}

void		players_line_refresh(t_vdata *vdata)
{
	int				player;
	int				ratio[4];
	int				total_ratio;
	long long int	ratio_sum;

	player = 0;
	ratio_sum = 0;
	total_ratio = 0;
	while (player < vdata->total_champs)
		ratio_sum += vdata->color_map_div[player++];
	calculate_ratio(vdata, ratio, ratio_sum);
	player = 0;
	werase(vdata->players_window);
	while (player < vdata->total_champs)
	{
		wattron(vdata->players_window,
			COLOR_PAIR(player + 1 + vdata->design * 10) | A_REVERSE);
		mvwprintw(
			vdata->players_window, total_ratio, 0, "%*s", ratio[player], "");
		wattroff(vdata->players_window,
			COLOR_PAIR(player + 1 + vdata->design * 10) | A_REVERSE);
		total_ratio += ratio[player];
		player++;
	}
	wrefresh(vdata->players_window);
}
