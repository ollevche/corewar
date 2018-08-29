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
		(void)vdata;
		refresh();
		system("printf \'\033[8;78;244t\'");
		//system("printf \'\033[8;68;251t\'");
		//ft_printf("Minimum window is %d columns and %d height.\n", W_WIDTH, W_HEIGHT); // test
		//delwin(vdata->left_window);
		//delwin(vdata->right_window);
		//endwin();
		//exit(1);
		//return (0);
	}
	return (1);
}

static void		set_defaults(t_vdata *vdata, t_champ *champs)
{
	vdata->left_window = newwin(66 , 195, 2, 0);
	vdata->right_window = newwin(20, 49, 2, 195);
	vdata->alert_window = newwin(14 , 59, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
	vdata->input_window = newwin(1, 12, 6, 219);
	vdata->authors = newwin(2, 195, 0, 0);
	vdata->key = 0;
	vdata->paused = 1;
	vdata->sec = 5;
	vdata->scrolling_names = NULL;
	vdata->scrolling_controls = NULL;
	vdata->time = 0;
	vdata->input_cycle = 0;
	vdata->input_entered = 0;
	vdata->input_index = 0;
	ft_bzero(vdata->input_line, 10);
	vdata->input_paused = 0;
	vdata->total_champs = get_total_champs(champs);
	vdata->last_win_cols_size = COLS;
	vdata->last_win_lines_size = LINES;
	vdata->active_alert = 0;
	vdata->live_bars = NULL;

	vdata->author_adv_switch = 1;
	vdata->author_time = 0;
	vdata->first_run = 1;

    ft_bzero(vdata->prev_map, sizeof(t_uchar) * MEM_SIZE);
    ft_bzero(vdata->prev_spot_map, sizeof(int) * MEM_SIZE);
}
int		get_total_champs(t_champ *champ)
{
	int players;

	players = 0;
	while(champ && (champ = champ->next))
		players++;
	return (++players);
}

int		visu_initializing(t_vdata *vdata, t_arg *arg, t_champ *champs)
{
	if (!arg->is_visual)
		return (1);
	if (!initscr() || !appropriate_window(vdata))
		return (0);
	set_escdelay(0);
	keypad(stdscr, TRUE);
	set_defaults(vdata, champs);
	curs_set(0);	
	refresh();
	start_color();
	init_color(COLOR_WHITE, 400, 400, 400);


	init_color(COLOR_RED, 880-280, 880-280, 480-280);
	init_color(COLOR_GREEN, 450-180, 350-180, 490-180);
	init_color(COLOR_YELLOW, 100-280, 600-280, 600-280);
	init_color(COLOR_BLUE, 850 - 280, 0, 350-280);

	init_color(11, 880 + 120, 880+ 120, 480+ 120);
	init_color(12, 450+ 100, 350+ 100, 490+ 100);
	init_color(13, 100+ 200, 600+ 200, 600+ 200);
	init_color(14, 850+ 120, 80+ 120, 350+ 120);
	
	// init_color(COLOR_RED, 168 * 3 + 200, 33 * 3 + 200, 107 * 3 + 200);
	// init_color(COLOR_GREEN,   247 * 3 + 200, 219 * 3 + 200, 105 * 3 + 200);
	// init_color(COLOR_YELLOW, 236 * 3 + 200, 27 * 3 + 200, 75 * 3 + 200); 
	// init_color(COLOR_BLUE, 46 * 3 + 200, 149 * 3 + 200, 152 * 3 + 200);

	// init_color(11,168 * 3 + 400, 33 * 3 + 400, 107 * 3 + 400);
	// init_color(12,  247 * 3 + 400, 219 * 3 + 400, 105 * 3 + 400);
	// init_color(13, 236 * 3 + 400, 27 * 3 + 400, 75 * 3 + 400); 
	// init_color(14, 46 * 3 + 400, 149 * 3 + 400, 152 * 3 + 400);


	init_pair(GRAY, COLOR_WHITE, COLOR_BLACK);
	init_pair(GRAY_B, COLOR_BLACK, COLOR_WHITE);

    set_champs_for_visu(champs, vdata);

	box(vdata->left_window, 0, 0);
	box(vdata->right_window, 0, 0);
	scrolling_controls(vdata, 69, 197);
	
	live_bars_initializing(vdata, champs, 67, 33);
	author_line_initializing(vdata);
	return (1);
}

void    set_champs_for_visu(t_champ *champs, t_vdata *vdata)
{
    int color;
	int y;

	y = 69;
	color = 1;
	while (champs != NULL)
	{
		init_pair(color * 10, COLOR_BLACK, color);
		init_pair(color + 10, 10 + color, COLOR_BLACK);
		init_pair(color, color, COLOR_BLACK);
		scrolling_name(vdata, champs->name, y, 2);
		champs = champs->next;
		y += 2;
		color++;
	}
}

int show_cycles = true;

int		visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	//werase(vdata->right_window);
	if (!arg->is_visual)
		return (1);

	if (vdata->input_cycle && show_cycles)
	{
		timeout(0);
		vdata->key = getch();
		vdata->scrolling_controls->key = vdata->key;
		if (KEY(ESC))
			vdata->input_cycle = 0;
		else
		{
			scrolling_of_the_names(vdata);
			char *cycles = ft_itoa(game->cycle);
			show_cycles = true;	//SET TO FALSE TO RENDER THE LOADING WINDOW ONLY ONCE
			show_alert_window(vdata, "     Loading... Press [ESC] to abort!", show_cycles ? cycles : "The window is rendered only ONCE");
			ft_strdel(&cycles);
		}
	}
	if (game->cycle == vdata->input_cycle)
		vdata->input_cycle = 0;
			
	if (!vdata->input_cycle)
	{
		show_left(vdata, game, champs);
		show_right(vdata, game, champs);
		refresh_live_bars(vdata, FALSE);		
		playback_controls(vdata, game, champs);
	}
	if (game->carry_num <= 0 || game->cycle_to_die < 0)
		gameover_window(vdata, game, champs);
	return (0);
}

int		visu_finalizing(t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	wattroff(vdata->right_window, COLOR_PAIR(GRAY));
	// wattroff(vdata->left_window, COLOR_PAIR(GRAY));
	(void)game;
	(void)champs;
	scrolling_finalizing(vdata);
	live_bars_finalizing(vdata);
	delwin(vdata->left_window);
	delwin(vdata->right_window);
	delwin(vdata->alert_window);
	delwin(vdata->input_window);
	endwin();
	system("killall afplay");
	exit(1);
	return (0);
}

void	music_player()
{
	static int stop = 1;
	static int i = 0;

	noecho();
	if (stop == 0 && i <= 3)
	{
		system("killall afplay");
		stop = 1;
	}
	else if (stop == 1)
	{
		if (i == 0)
			system("afplay media/La_Valse_OST_Ameli.mp3 &");
		else if(i == 1)
			system("afplay media/Hooked_On_A_Feeling.mp3 &");
		else if(i == 2)
			system("afplay media/Game_of_Thrones.mp3 &");
		else
			timeout(0);
		stop = 0;
		i++;
	}
}