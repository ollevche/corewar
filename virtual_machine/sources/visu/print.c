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

void	show_left(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int	index;
	int y;
	int x;

	index = 0;
	y = 0;
	x = 2;
	(void)champs;
	while (index < MEM_SIZE)
	{

		if (index % 64 == 0)
		{
			y++;
			x = 2;
		}
			print_player_code(vdata->left_window, y, x, game->map[index], game->spot_map[index] * (-1));
		x += 3;
		index++;
	}
	show_carries(vdata, game, game->carries);
	wrefresh(vdata->left_window);
}

void	show_carries(t_vdata *vdata, t_session *game, t_carry *carries)
{
	int x;
	int y;
	int pc;

	while (carries != NULL)
	{
		pc = carries->pc;
		x = pc % 64 * 3 + 2;
		y = pc / 64 + 1;
		wattron(vdata->left_window, COLOR_PAIR(carries->champ * (-10)));
		mvwprintw(vdata->left_window, y, x, "%02x", game->map[pc]);
		wattroff(vdata->left_window, COLOR_PAIR(carries->champ * (-10)));
        mvwprintw(vdata->left_window, y, x + 2, " ");
		carries = carries->next;
	}
}
void print_player_code(WINDOW *left_window, int y, int x, t_uchar n, int player)
{
    if (player > 5 && player < 1)
        player = 0;
	wattron(left_window, COLOR_PAIR(player));

    //mvwaddchstr(left_window, y, x, L"333");
	//waddchstr
	mvwprintw(left_window, y, x, "%02x", n);
	wattroff(left_window, COLOR_PAIR(player));
}




void    show_right(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int y;

	y = 3;
	werase(vdata->right_window); //TODO delets box	
	wattron(vdata->right_window, COLOR_PAIR(0));
	if (vdata->paused)
	{
		wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED ** ");	
		wattroff(vdata->right_window, A_BOLD);
	}
	else
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** RUNNING **");
	//mvwprintw(vdata->right_window, 1, START_X, "%s", vdata->paused ? "** PAUSED ** " : "** RUNNING **");	
	mvwprintw(vdata->right_window, 2, START_X, "[Space] changes status");
	wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);
	mvwprintw(vdata->right_window, 2, START_X + 1, "Space");
	
	wattroff(vdata->right_window, A_BOLD);

	mvwprintw(vdata->right_window, 4, START_X, "Cycles/second:\t%d     ", vdata->sec);
	mvwprintw(vdata->right_window, 5, START_X, "[Left] and [Right] arrows change speed");
	wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);
	mvwprintw(vdata->right_window, 5, START_X + 1, "Left");
	mvwprintw(vdata->right_window, 5, START_X + 12, "Right");
	
	wattroff(vdata->right_window, A_BOLD);
	

	wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);

	mvwprintw(vdata->right_window, y += 4, START_X, "Current cycle:\t%d", game->cycle);

	wattroff(vdata->right_window, COLOR_PAIR(0) | A_BOLD);	
	mvwprintw(vdata->right_window, y += 1, START_X, "[E] Enter a cycle");
	
	//show_players(vdata->right_window, champs, &y);
	mvwprintw(vdata->right_window, y += 3, START_X,"Carries:\t%d", game->carry_num);
	mvwprintw(vdata->right_window, y += 2, START_X, "Cycle to die: %d\tLast change:  %d",
		game->cycle_to_die, game->last_ctd);
	mvwprintw(vdata->right_window, y += 2, START_X,  "LIVES:\t%d", game->period_lives);
	mvwprintw(vdata->right_window, y += 2, START_X, "LAST ALIVE:");

	
	if (game->last_alive != NULL)
	{
		wattron(vdata->right_window, COLOR_PAIR(game->last_alive->id * (-1)));
		mvwprintw(vdata->right_window, y, START_X + 11, "\t%s", game->last_alive->name);
		wattroff(vdata->right_window, COLOR_PAIR(game->last_alive->id * (-1)));
	}
	else
		mvwprintw(vdata->right_window, y, START_X + 11, "\tNO ONE");


	wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);
	mvwprintw(vdata->right_window, 8, START_X + 1, "E");
	wattroff(vdata->right_window, A_BOLD);
	wrefresh(vdata->right_window);

// TODO TEMP
	if (vdata->input_entered)
	{
		wattron(vdata->input_window, COLOR_PAIR(0) | A_BOLD);
		mvwprintw(vdata->input_window, 0, 0, "%s", "_________");
		if (vdata->input_index)
			mvwprintw(vdata->input_window, 0, 0, "%s", vdata->input_line);
		wattroff(vdata->input_window, COLOR_PAIR(0) | A_BOLD);	
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
