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

void init_design(int design, int total_champs)
{
	int player;

	if (design == 0)
	{
		init_color(1, 168 * 3 , 33 * 3 , 107 * 3);
		init_color(2, 247 * 3 , 219 * 3 , 105 * 3);
		init_color(3, 236 * 3 , 27 * 3 , 75 * 3);
		init_color(4, 46 * 3 , 149 * 3 , 152 * 3);

		init_color(11,168 * 3 + 200, 33 * 3 + 200, 107 * 3 + 200);
		init_color(12,  247 * 3 + 200, 219 * 3 + 200, 105 * 3 + 200);
		init_color(13, 236 * 3 + 200, 27 * 3 + 200, 75 * 3 + 200);
		init_color(14, 46 * 3 + 200, 149 * 3 + 200, 152 * 3 + 200);
	}
	else if (design == 2)
	{
		init_color(21, 0, 500, 453);
		init_color(22, 256, 333, 470);
		init_color(23, 830, 673, 556);
		init_color(24, 136, 560, 570);

		init_color(31, 0 + 200, 500 + 200, 453 + 200);
		init_color(32, 256 + 200, 333 + 200, 470 + 200);
		init_color(33, 830 + 170, 673 + 170, 556 + 170);
		init_color(34, 136 + 200, 560 + 200, 570 + 200);
	}
	else if (design == 4)
	{
		init_color(41, 670, 503, 456);
		init_color(42, 443, 226, 220);
		init_color(43, 250, 186, 166);
		init_color(44, 746, 560, 510);

		init_color(51, 670 + 200, 503 + 200, 456 + 200);
		init_color(52, 443 + 200, 226 + 200, 220 + 200);
		init_color(53, 250 + 200, 186 + 200, 166 + 200);
		init_color(54, 746 + 200, 560 + 200, 510 + 200);
	}
	else if (design == 6)
	{
		init_color(61, 826, 590, 496);
		init_color(62, 820, 380, 426);
		init_color(63, 640, 360, 440);
		init_color(64, 360, 303, 410);

		init_color(71, 1000, 590 + 200, 496 + 200);
		init_color(72, 1000, 380 + 200, 426 + 200);
		init_color(73, 640 + 200, 360 + 200, 440 + 200);
		init_color(74, 360 + 200, 303 + 200, 410 + 200);
	}

	player = 1;
	while (player <= total_champs)
	{
		init_pair(player + (design * 10), player + (design * 10), COLOR_BLACK);
		init_pair(player + (design + 1) * 10, player + (design + 1) * 10, COLOR_BLACK);
		player++;
	}
}

int		change_design(t_vdata *vdata, t_session *game, t_champ *champs)
{
	t_console *tmp_console;

	tmp_console = &vdata->console;
	if (KEY('d') || KEY('D'))
	{
		vdata->design = (vdata->design + 2) % (N_DESIGNS * 2);
		if (vdata->set_design[vdata->design/2] == 0)
		{
			init_design(vdata->design,  vdata->total_champs);
			vdata->set_design[vdata->design/2] = 1;
		}
		tmp_console->refresh = 1;
		if (console_refresh(vdata) != 0)
			return (-1);
		refresh_scroll_names(vdata);
		players_line_refresh(vdata);
		show_left(vdata, game, champs);
		show_right(vdata, game, champs);
		refresh_live_bars(vdata, TRUE);
		wrefresh(vdata->scrolling_names->window);
	}
	return (0);
}

int     get_color(t_champ *champs, int id)
{
	int i;

	i = 1;
	while (champs != NULL)
	{
		if (champs->id == id)
			return (i);
		i++;
		champs = champs->next;
	}
	return (0);
}

void	show_left(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int	index;
	int y;
	int x;

	index = 0;
	y = 0;
	x = 2;
	(void)champs;
	ft_bzero(vdata->color_map_div, sizeof(long long int) * 4);
	while (index < MEM_SIZE)
	{
		if (index % 64 == 0)
		{
			y++;
			x = 2;
		}
		print_player_code(vdata, y, x, game->map, game->spot_map, index, champs);
		vdata->prev_map[index] = game->map[index];
		vdata->prev_spot_map[index] = game->spot_map[index];
		x += 3;
		index++;
	}
	show_carries(vdata, game, game->carries, champs);
	wrefresh(vdata->left_window);
}

void	show_carries(t_vdata *vdata, t_session *game, t_carry *carries, t_champ *champs)
{
	int x;
	int y;
	int pc;

	while (carries != NULL)
	{
		pc = carries->pc;
		x = pc % 64 * 3 + 2;
		y = pc / 64 + 1;
		wattron(vdata->left_window, COLOR_PAIR(get_color(champs, carries->champ) + vdata->design * 10) | A_REVERSE);
		mvwprintw(vdata->left_window, y, x, "%02x", game->map[pc]);
		wattroff(vdata->left_window, COLOR_PAIR(get_color(champs, carries->champ) + vdata->design * 10) | A_REVERSE);
		mvwprintw(vdata->left_window, y, x + 2, " ");
		carries = carries->next;
	}
}
void print_player_code(t_vdata *vdata, int y, int x, t_uchar *map, int *spot_map, int index, t_champ *champs)
{
	static int i = 0;
	int color;

	color = get_color(champs, spot_map[index]);
	if (color != 0)
	{
		vdata->color_map_div[color - 1]++;
		if (i <= MEM_SIZE || (vdata->prev_map[index] == map[index] && vdata->prev_spot_map[index] == spot_map[index]))
		{
			wattron(vdata->left_window, COLOR_PAIR(color + (vdata->design * 10)));
			mvwprintw(vdata->left_window, y, x, "%02x", map[index]);
			wattroff(vdata->left_window, COLOR_PAIR(color+ (vdata->design * 10)));
		}
		else
		{
			wattron(vdata->left_window, COLOR_PAIR(color + ((vdata->design + 1) * 10)));
			mvwprintw(vdata->left_window, y, x, "%02x", map[index]);
			wattroff(vdata->left_window, COLOR_PAIR(color + ((vdata->design + 1) * 10)));
		}
	}
	else
	{
		wattron(vdata->left_window, COLOR_PAIR(GRAY));
		mvwprintw(vdata->left_window, y, x, "%02x", map[index]);
		wattroff(vdata->left_window, COLOR_PAIR(GRAY));
	}
	i++;
}

void    show_right(t_vdata *vdata, t_session *game, t_champ *champs)
{
	(void)champs;
	int y;

	y = 3;
	werase(vdata->right_window); //TODO delets box
	wattron(vdata->right_window, COLOR_PAIR(GRAY));
	if (vdata->paused)
	{
		wattron(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED ** ");
		wattroff(vdata->right_window, A_BOLD);
	}
	else
		mvwprintw(vdata->right_window, 1, 17, "%s", "-- RUNNING --");
	wattroff(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, 2, START_X, "[Space] changes status");
	wattron(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, 2, START_X + 1, "Space");
	wattroff(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, 4, START_X, "Cycles/second:\t%d", vdata->sec);
	mvwprintw(vdata->right_window, 5, START_X, "[Left] and [Right] arrows change speed");
	wattron(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, 5, START_X + 1, "Left");
	mvwprintw(vdata->right_window, 5, START_X + 12, "Right");
	wattroff(vdata->right_window, A_BOLD);

	wattron(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);

	mvwprintw(vdata->right_window, y += 4, START_X, "Current cycle:\t%d", game->cycle);

	wattroff(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, y += 1, START_X, "[E] Enter a cycle");

	//show_players(vdata->right_window, champs, &y);
	mvwprintw(vdata->right_window, y += 3, START_X,"Carries:\t%d", game->carry_num);
	mvwprintw(vdata->right_window, y += 2, START_X,"Cycle to die: %d", game->cycle_to_die);
	mvwprintw(vdata->right_window, y += 2, START_X,"Last change:  %d", game->last_ctd);
	mvwprintw(vdata->right_window, y += 2, START_X,  "LIVES:\t%d", game->period_lives);
	mvwprintw(vdata->right_window, y += 2, START_X, "LAST ALIVE:");


	if (game->last_alive != NULL)
	{
		wattroff(vdata->right_window, A_BOLD);
		wattron(vdata->right_window, COLOR_PAIR(get_color(champs, game->last_alive->id) + (vdata->design * 10)));
		mvwprintw(vdata->right_window, y, START_X + 11, "\t%s", game->last_alive->name);
		wattroff(vdata->right_window,  COLOR_PAIR(get_color(champs, game->last_alive->id) + (vdata->design * 10)));
	}
	else
		mvwprintw(vdata->right_window, y, START_X + 11, "\tNO ONE");

	mvwprintw(vdata->right_window, y += 2, START_X, "[S] Make one step forward");
	mvwprintw(vdata->right_window, y += 2, START_X, "[C] Open\\Close Console");

	wattron(vdata->right_window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(vdata->right_window, 8, START_X + 1, "E");
	mvwprintw(vdata->right_window, y - 2 , START_X + 1, "S");
	mvwprintw(vdata->right_window, y - 2 , START_X + 30, ">> NEW <<");


	mvwprintw(vdata->right_window, y, START_X + 1, "C");
	mvwprintw(vdata->right_window, y, START_X + 30, ">> NEW <<");

	wattroff(vdata->right_window, A_BOLD);

	wrefresh(vdata->right_window);

// TODO TEMP
	if (vdata->input_entered)
	{
		wattron(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		mvwprintw(vdata->input_window, 0, 0, "%s", "_________");
		if (vdata->input_index)
			mvwprintw(vdata->input_window, 0, 0, "%s", vdata->input_line);
		wattroff(vdata->input_window, COLOR_PAIR(GRAY) | A_BOLD);
		wrefresh(vdata->input_window);
	}

}

// void show_players(WINDOW *right_window, t_champ *champs, int *y)
// {
// 	// init_pair(, COLOR_GREEN, COLOR_BLACK);
// 	//wattron(right_window, COLOR_PAIR(5));
// 	//mvwprintw(right_window, *y, 25 - 3, "PLAYERS");
// 	int player;
// 	player = 1;
// 	*y += 3;
// 	while (champs != NULL)
// 	{
// 		wattron(right_window, COLOR_PAIR(player));
// 		mvwprintw(right_window, *y, START_X, "Player %d:",  champs->id);

// 		//mvwprintw(right_window, *y, START_X, "Player %d:   %s",  champs->id, champs->name);
// 		wattroff(right_window, COLOR_PAIR(player));
// 		// mvwprintw(right_window, *y += 1, START_X, "Last live: %d", 0);
// 		// mvwprintw(right_window, *y += 1, START_X, "Lives in current period: %d", 0);

// 		(*y) += 2;
// 		player++;
// 		champs = champs->next;
// 	}
// }
