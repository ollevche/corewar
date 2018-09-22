/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblokha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 15:23:09 by vblokha           #+#    #+#             */
/*   Updated: 2018/08/17 15:23:10 by vblokha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	show_carries(
	t_vdata *vdata, t_session *game, t_carry *carries, t_champ *champs)
{
	int x;
	int y;
	int pc;

	while (carries != NULL)
	{
		pc = carries->pc;
		x = pc % 64 * 3 + 2;
		y = pc / 64 + 1;
		wattron(vdata->left_window, COLOR_PAIR(get_color(champs,
			carries->champ) + vdata->design * 10) | A_REVERSE);
		mvwprintw(vdata->left_window, y, x, "%02x", game->map[pc]);
		wattroff(vdata->left_window, COLOR_PAIR(get_color(champs,
			carries->champ) + vdata->design * 10) | A_REVERSE);
		mvwprintw(vdata->left_window, y, x + 2, " ");
		carries = carries->next;
	}
}

static void	print_player_code_option_1(
	t_vdata *vdata, int color, int norma_sucks[])
{
	int y;
	int x;
	int index;

	y = norma_sucks[0];
	x = norma_sucks[1];
	index = norma_sucks[2];
	wattron(vdata->left_window, COLOR_PAIR(color + (vdata->design * 10)));
	mvwprintw(vdata->left_window, y, x, "%02x", vdata->game->map[index]);
	wattroff(vdata->left_window, COLOR_PAIR(color + (vdata->design * 10)));
}

static void	print_player_code_option_2(
	t_vdata *vdata, int color, int norma_sucks[])
{
	int y;
	int x;
	int index;

	y = norma_sucks[0];
	x = norma_sucks[1];
	index = norma_sucks[2];
	wattron(vdata->left_window,
		COLOR_PAIR(color + ((vdata->design + 1) * 10)));
	mvwprintw(vdata->left_window, y, x, "%02x", vdata->game->map[index]);
	wattroff(vdata->left_window,
		COLOR_PAIR(color + ((vdata->design + 1) * 10)));
}

static void	print_player_code(t_vdata *vdata, int y, int x, int index)
{
	static int	i = 0;
	int			color;
	int			norma_sucks[3];

	norma_sucks[0] = y;
	norma_sucks[1] = x;
	norma_sucks[2] = index;
	color = get_color(vdata->champs, vdata->game->spot_map[index]);
	if (color != 0)
	{
		vdata->color_map_div[color - 1]++;
		if (i <= MEM_SIZE || (vdata->prev_map[index] == vdata->game->map[index]
			&& vdata->prev_spot_map[index] == vdata->game->spot_map[index]))
			print_player_code_option_1(vdata, color, norma_sucks);
		else
			print_player_code_option_2(vdata, color, norma_sucks);
	}
	else
	{
		wattron(vdata->left_window, COLOR_PAIR(GRAY));
		mvwprintw(vdata->left_window, y, x, "%02x", vdata->game->map[index]);
		wattroff(vdata->left_window, COLOR_PAIR(GRAY));
	}
	i++;
}

void		show_left(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int	index;
	int y;
	int x;

	index = 0;
	y = 0;
	x = 2;
	ft_bzero(vdata->color_map_div, sizeof(long long int) * 4);
	while (index < MEM_SIZE)
	{
		if (index % 64 == 0)
		{
			y++;
			x = 2;
		}
		print_player_code(vdata, y, x, index);
		vdata->prev_map[index] = game->map[index];
		vdata->prev_spot_map[index] = game->spot_map[index];
		x += 3;
		index++;
	}
	show_carries(vdata, game, game->carries, champs);
	wrefresh(vdata->left_window);
}
