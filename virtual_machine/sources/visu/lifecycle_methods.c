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

static int  appropriate_window(t_vdata *vdata)
{


	if (COLS < W_WIDTH || LINES < W_HEIGHT)
	{  
		ft_printf("Minimum window is %d columns and %d height.\n", W_WIDTH, W_HEIGHT); // test
		delwin(vdata->left_window);
		delwin(vdata->right_window);
		endwin();
		exit(1);
		return (0);
	}
	return (1);
}

int		visu_initializing(t_vdata *vdata, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	if (!initscr() || !appropriate_window(vdata))
		return (0);
	set_escdelay(0);
	keypad(stdscr, TRUE);

	vdata->left_window = newwin(66 , 195, 0, 0);
	vdata->right_window = newwin(30, 50, 0, 195);
	vdata->sec = 5;
	vdata->key = 0;
	vdata->paused = 1;
	vdata->scrolling_names = NULL;
	vdata->scrolling_controls = NULL;
	vdata->time = 0;
	vdata->time2 = 0;

	vdata->vasya = 0;
	vdata->skip = 0;
	vdata->index = 0;
	vdata->user_input = 0;
	ft_bzero(vdata->user_cycle, 10);

	nodelay(vdata->left_window, TRUE);
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
	
	init_pair(141, COLOR_GREEN, COLOR_BLACK);
	scrolling_name(vdata, "REALLY Fucking Viktoriya. Yes she is", 30, 212);
	scrolling_name(vdata, "Serzh Ivasyshyn", 35, 212);
	scrolling_name(vdata, "Sasha Levchenkov", 40, 212);
	scrolling_name(vdata, "Dariy Pozinenko", 45, 212);	
	scrolling_controls(vdata, 50, 198);
	
	return (1);
}

int		visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);

	if (game->cycle == vdata->skip)
		vdata->skip = 0;


	if (vdata->vasya)
	{
		vdata->paused = 1;
		vdata->vasya = 0;
	}

	if (vdata->skip <= game->cycle || !vdata->skip)
	{
		show_left(vdata->left_window, game, champs);
		show_right(vdata, game, champs);
		playback_controls(vdata, game, champs);
		refresh();
	}

	if (game->carry_num <= 0 || game->cycle_to_die <0)
	{
		show_left(vdata->left_window, game, champs);
		show_right(vdata, game, champs);
	}


	return (0);
}

int		visu_finalizing(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);

	
	playback_controls(vdata, game, champs);
	delwin(vdata->left_window);
	delwin(vdata->right_window);
	endwin();
	exit(1);
	return (0);
}
