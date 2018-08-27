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
		system("printf \'\033[8;76;244t\'");
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
	vdata->left_window = newwin(66 , 195, 0, 0);
	vdata->right_window = newwin(20, 49, 0, 195);
	vdata->alert_window = newwin(14 , 59, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
	vdata->input_window = newwin(1, 12, 6, 219);
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
}
int count_champs(t_champ *champs)
{
	int count;

	count = 0;
	while (champs != NULL)
	{		
		champs = champs->next;
		count++;
	}
	return (count);
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
	init_color(COLOR_GREEN, 880, 880, 480);
	init_color(COLOR_RED, 450, 350, 490);
	init_color(COLOR_YELLOW, 300, 800, 800);
	init_color(COLOR_BLUE, 850, 80, 350);


	init_pair(LEFT_W, COLOR_RED, COLOR_BLACK);
	init_pair(100, COLOR_BLACK, COLOR_WHITE);
	wattron(vdata->right_window, COLOR_PAIR(LEFT_W) | A_BOLD);

	
	int color;
	int y;

	y = 67;
	color = 1;

	t_champ *champs2 = champs;
	while (color <= vdata->total_champs)
	{
		init_pair(color * 10, COLOR_BLACK, color);
		init_pair(color, color, COLOR_BLACK);
		scrolling_name(vdata, champs2->name, y, 2);
		champs2 = champs2->next;
		y += 2;
		color++;
	}
	
	wattroff(vdata->right_window, COLOR_PAIR(LEFT_W) | A_BOLD);

	box(vdata->left_window, 0, 0);
	box(vdata->right_window, 0, 0);
	scrolling_controls(vdata, 67, 197);

	live_bars_initializing(vdata, champs, 65, 33);

	return (1);
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
	wattroff(vdata->right_window, COLOR_PAIR(LEFT_W));
	// wattroff(vdata->left_window, COLOR_PAIR(LEFT_W));
	(void)game;
	(void)champs;
	scrolling_finalizing(vdata);
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