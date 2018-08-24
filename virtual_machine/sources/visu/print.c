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
			print_player_code(vdata->left_window, y, x, game->map[index], 0);
		x += 3;
		index++;
	}
	show_carries(vdata, game, game->carrys);
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
		wattron(vdata->left_window, COLOR_PAIR(CARRY_P1));
		mvwprintw(vdata->left_window, y, x, "%02x", game->map[pc]);
		wattroff(vdata->left_window, COLOR_PAIR(CARRY_P1));
        mvwprintw(vdata->left_window, y, x + 2, " ");
		carries = carries->next;
	}
}
void print_player_code(WINDOW *left_window, int y, int x, t_uchar n, int player)
{
	wattron(left_window, COLOR_PAIR(player));
	mvwprintw(left_window, y, x, "%02x", n);
	wattroff(left_window, COLOR_PAIR(player));
}




void    show_right(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int y;

	y = 3;

	//werase(vdata->right_window);
	wattron(vdata->right_window, COLOR_PAIR(0));

	mvwprintw(vdata->right_window, 1, START_X, "%s", vdata->paused ? "** PAUSED ** " : "** RUNNING **");	
		
	mvwprintw(vdata->right_window, 3, START_X, "Cycles/second:\t%d     ", vdata->sec);

	wattron(vdata->right_window, COLOR_PAIR(0) | A_BOLD);

	mvwprintw(vdata->right_window, y += 2, START_X, "Current cycle:\t%d", game->cycle);

	wattroff(vdata->right_window, COLOR_PAIR(0) | A_BOLD);	
	mvwprintw(vdata->right_window, y += 1, START_X, "[E] Enter a cycle");
	
	//show_players(vdata->right_window, champs, &y);
	mvwprintw(vdata->right_window, y += 5, START_X,"Carries:\t%d", game->carry_num);
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
	mvwprintw(vdata->right_window, 6, START_X + 1, "E");
	wattroff(vdata->right_window, A_BOLD);
	wrefresh(vdata->right_window);

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
