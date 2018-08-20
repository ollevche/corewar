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

int	is_carry(t_carry *carrys, int index)
{
	while (carrys != NULL)
	{
		if (carrys->pc == index)
			return (1);
		carrys = carrys->next;
	}
	return (0);
}

void	show_left(WINDOW *left_window, t_session *game, t_champ *champs)
{
	int	index;
	int y;
	int x;

	index = 0;
	y = 0;
	x = 2;
	while (index < MEM_SIZE)
	{

		if (index % 64 == 0)
		{
			y++;
			x = 2;
		}
		if (is_carry(game->carrys, index) != 0)
		{
			wattron(left_window, COLOR_PAIR(CARRY_COLOR_PAIR));
			mvwprintw(left_window, y, x, "%02x", game->map[index]);
			wattroff(left_window, COLOR_PAIR(CARRY_COLOR_PAIR));
            mvwprintw(left_window, y, x + 2, " ");
		}
		else
			mvwprintw(left_window, y, x, "%02x", game->map[index]);
		x += 3;
		index++;
	}
	
	wrefresh(left_window);
}

void    show_right(t_vdata *vdata, t_session *game, t_champ *champs)
{
	int y;

	y = 3;

mvwprintw(vdata->right_window, 3, START_X, "Cycles/second:\t%d     ", vdata->sec);

	mvwprintw(vdata->right_window, y += 2, START_X, "Total cycle:\t\t%d", game->cycle);
	mvwprintw(vdata->right_window, y += 1, START_X, "Current cycle:\t%d", 0);
	show_players(vdata->right_window, champs, &y);
	mvwprintw(vdata->right_window, y += 2, START_X,"Carrys:\t%d", game->carry_num);
	mvwprintw(vdata->right_window, y += 2, START_X, "Cycle to die: %d\tLast change:  %d",
		game->cycle_to_die, game->last_ctd);
	mvwprintw(vdata->right_window, y += 2, START_X, "PERIOD LIVES:\t%d", game->period_lives);
	mvwprintw(vdata->right_window, y += 2, START_X, "LAST ALIVE:");
	if (game->last_alive != NULL)
		mvwprintw(vdata->right_window, y, START_X + 11, "\t%s", game->last_alive->name);
	else
		mvwprintw(vdata->right_window, y, START_X + 11, "\tNO ONE");
	wrefresh(vdata->right_window);
}

void show_players(WINDOW *right_window, t_champ *champs, int *y)
{
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	//wattron(right_window, COLOR_PAIR(5));
	//mvwprintw(right_window, *y, 25 - 3, "PLAYERS");
	*y += 3;
	while (champs != NULL)
	{
		mvwprintw(right_window, *y, START_X, "Player %d:   %s",  champs->id, champs->name);
		mvwprintw(right_window, *y += 1, START_X, "Last live: %d", 0);		
		mvwprintw(right_window, *y += 1, START_X, "Lives in current period: %d", 0);
		
		(*y) += 2;
		champs = champs->next;
	}
}
