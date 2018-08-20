/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:07:33 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/16 16:07:34 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static int  appropriate_window(t_vdata *vdata, t_arg *arg)
{
	if (COLS < W_WIDTH || LINES < W_HEIGHT)
	{  
		visu_finalizing(vdata, arg);
		ft_printf("Minimum window is %d columns and %d height.\n", W_WIDTH, W_HEIGHT);
		return (0);
	}
	return (1);
}

int		visu_initializing(t_vdata *vdata, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	if (!initscr() || !appropriate_window(vdata, arg))
		return (0);
	keypad(stdscr, TRUE);	
	vdata->left_window = newwin(66 , 195, 0, 0);
	vdata->right_window = newwin(66, 50, 0, 195);
	vdata->sec = 1;
	vdata->key = 0;
	vdata->paused = 1;

	nodelay(vdata->left_window, FALSE);
	nodelay(vdata->right_window, FALSE);
	curs_set(0);
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_color(COLOR_WHITE, 200, 300, 300);
	init_pair(CARRY_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
	init_pair(14, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	
	wattron(vdata->left_window, COLOR_PAIR(14));
	
	box(vdata->left_window, 0, 0);
	box(vdata->right_window, 0, 0);
	return (1);
}

int		visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	refresh();
	show_left(vdata->left_window, game, champs);
	show_right(vdata, game, champs);
	playback_controls(vdata);
	return (0);
}

int		visu_finalizing(t_vdata *vdata, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	usleep(20000000);
	delwin(vdata->left_window);
	delwin(vdata->right_window);
	endwin();
	return (0);
}
