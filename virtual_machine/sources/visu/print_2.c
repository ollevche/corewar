/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 21:56:51 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 21:56:52 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
**	norme
*/

#define ID game->last_alive->id
#define DESIGN vdata->design

static void	show_right_stage_regular(
	t_vdata *vdata, int y, t_session *game, t_champ *champs)
{
	WINDOW * win;
	win = vdata->right_window;
	wattron(win, COLOR_PAIR(GRAY));
	mvwprintw(win, y += 3, START_X, "[Space] changes status");
	mvwprintw(win, y += 2, START_X, "Cycles/second:\t%d", vdata->sec);
	mvwprintw(win, y += 1, START_X, "[Left] and [Right] arrows change speed");
	mvwprintw(win, y += 3, START_X, "[E] Enter a cycle");
	mvwprintw(win, y += 2, START_X, "Carries:\t\t%d", game->carry_num);
	mvwprintw(win, y += 1, START_X, "Cycle to die:\t\t%d", game->cycle_to_die);
	mvwprintw(win, y += 1, START_X, "Last change:\t\t%d", game->last_ctd);
	mvwprintw(win, y += 1, START_X, "Lives:\t\t%d", game->period_lives);
	mvwprintw(win, y += 1, START_X, "Last alive:");
	if (game->last_alive)
	{
		wattron(win, COLOR_PAIR(get_color(champs, ID) + (DESIGN * 10)));
		mvwprintw(win, y, START_X + 11, "\t\t%s", game->last_alive->name);
		wattroff(win, COLOR_PAIR(get_color(champs, ID) + (DESIGN * 10)));
	}
	else
		mvwprintw(win, 14, START_X + 11, "\t\tNo one");
	mvwprintw(win, y += 2, START_X, "[S] Makes one step forward");
	mvwprintw(win, y += 2, START_X, "[C] Opens\\Closes Coreware console");
	mvwprintw(win, y += 2, START_X, "[D] Changes design");
	mvwprintw(win, y += 2, START_X, "[M] On\\Off music");
	wattroff(win, COLOR_PAIR(GRAY));
}

static void	show_right_stage_bold(t_vdata *vdata, int y, t_session *game)
{
	WINDOW * win;
	win = vdata->right_window;
	wattron(win, COLOR_PAIR(GRAY) | A_BOLD);
	if (vdata->paused)
		mvwprintw(win, 1, START_X, "%s", "** PAUSED ** ");
	else
		mvwprintw(win, 1, 17, "%s", "** RUNNING **");
	mvwprintw(win, y += 3, START_X + 1, "Space");
	mvwprintw(win, y += 3, START_X + 1, "Left");
	mvwprintw(win, y, START_X + 12, "Right");
	mvwprintw(win, y += 2, START_X, "Current cycle:\t%d", game->cycle);
	mvwprintw(win, y += 1, START_X + 1, "E");
	mvwprintw(win, y += 8, START_X + 1, "S");
	mvwprintw(win, y += 2, START_X + 1, "C");
	mvwprintw(win, y += 2, START_X + 1, "D");
	mvwprintw(win, y += 2, START_X + 1, "M");
	wattroff(win, COLOR_PAIR(GRAY) | A_BOLD);
}

void		show_right(t_vdata *vdata, t_session *game, t_champ *champs)
{
	werase(vdata->right_window);
	show_right_stage_regular(vdata, 0, game, champs);
	show_right_stage_bold(vdata, 0, game);
	wrefresh(vdata->right_window);
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
