/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playback_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:35:44 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/19 14:35:45 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		key_listener(t_vdata *vdata, t_session *game, t_champ *champs)
{
// 

	// WINDOW *bye2;
	//  	bye2 = newwin(3 , 33, 3, 3);
	//  	mvwprintw(bye2, 1, 1, "%d", vdata->key);
	// 	wrefresh(bye2);


	if (vdata->key == 127)
	{
		//exit(1);
		if (vdata->index > 0)
		{
			vdata->user_cycle[--vdata->index] = '\0';
			WINDOW *bye;
			bye = newwin(3 , 12, 4, 228);

wattron(bye, COLOR_PAIR(141) | A_BOLD);
			mvwprintw(bye, 1, 1, "%s", vdata->user_cycle);
			
			wattroff(bye, A_BOLD);	
			wrefresh(bye);
		}

	}


	if (vdata->user_input && (vdata->key >= '0' && vdata->key <= '9'))

	{
		if (ft_strlen(vdata->user_cycle) < 10)
		{
			vdata->user_cycle[vdata->index++] = vdata->key;

			WINDOW *bye;
		 	bye = newwin(3 , 12, 4, 228);
wattron(bye, COLOR_PAIR(141) | A_BOLD);
 		
			mvwprintw(bye, 1, 1, "%s", vdata->user_cycle);

			wattroff(bye, A_BOLD);	
			wrefresh(bye);
		}

	}

	if (vdata->key == 'e' || vdata->key == 'E')
	{
		WINDOW *bye;
	 	bye = newwin(3 , 12, 4, 228);
	 	mvwprintw(bye, 1, 1, "%s", "          ");
		wrefresh(bye);

		vdata->user_input = vdata->user_input ? 0 : 1;
		ft_bzero(vdata->user_cycle, 10);
		vdata->index = 0;
	}


	if (vdata->key == 27)
		{
			vdata->key = 0;
			WINDOW *bye3;
 			bye3 = newwin(14 , 59, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);


			wattron(bye3, COLOR_PAIR(141) | A_BOLD);
		 	mvwprintw(bye3, 9, 14, "%s", "Are you sure you want to exit?");
		 	mvwprintw(bye3, 11, 17, "%s", "[Y] Yes           No [N]");
			box(bye3, 0, 0);
			wattroff(bye3, A_BOLD);			


			wrefresh(bye3);

			while (!(vdata->key == 121 || vdata->key == 27 || vdata->key == 110))
		 		vdata->key = getch();
		 	if (vdata->key == 121)
		 	{
		 		scrolling_finalizing(vdata);
		 		delwin(vdata->left_window);
				delwin(vdata->right_window);
				endwin();
				exit(1);
		 	}

		 	if (vdata->paused)
		 		show_left(vdata->left_window, game, champs);
		}



			timeout(1000 / vdata->sec);
			vdata->key = getch();


	if (vdata->user_input && vdata->key == '\n')
	{
vdata->key = 0;

		vdata->skip = ft_atoi(vdata->user_cycle);


		WINDOW *bye2;
	 	bye2 = newwin(3 , 12, 4, 228);
	 	mvwprintw(bye2, 1, 1, "%s", "          ");
		wrefresh(bye2);

		vdata->user_input = vdata->user_input ? 0 : 1;
		ft_bzero(vdata->user_cycle, 10);
		vdata->index = 0;

		if (vdata->skip > game->cycle)
		{


			if (vdata->paused)
			{
				vdata->key = 32;
				vdata->vasya = 1;
			}

		}
		else if (vdata->skip < game->cycle)
		{
			WINDOW *bye3;
		 	bye3 = newwin(14 , 59, W_HEIGHT / 2 - 7, W_WIDTH / 2 - 30);
		 	wattron(bye3, COLOR_PAIR(141) | A_BOLD);
		 	mvwprintw(bye3, 9, 8, "%s", "Unfortunately, you can't go back in time!");
		 	mvwprintw(bye3, 11, 17, "%s", "Press [Enter] to continue.");
			box(bye3, 0, 0);
			wattroff(bye3, A_BOLD);			
		 	wrefresh(bye3);
		 	while (!(vdata->key == '\n' || vdata->key == 27))
		 		vdata->key = getch();
		 	vdata->key = -1;
		 	if (vdata->paused)
		 		show_left(vdata->left_window, game, champs);
		}



	}


	vdata->scrolling_controls->key = vdata->key;

	scrolling_of_the_names(vdata);

	if (vdata->key == KEY_LEFT && vdata->sec > 10)
		vdata->sec -= 5;

	if (vdata->key == KEY_RIGHT && vdata->sec < 1000)
		vdata->sec += 5;
	if (vdata->key > 0)
	{
		mvwprintw(vdata->right_window, 3, START_X, "Cycles/second:\t%d     ", vdata->sec);
		wrefresh(vdata->right_window);
	}
}

void	playback_controls(t_vdata *vdata, t_session *game, t_champ *champs)
{
	noecho();
	if (vdata->paused == 1)
	{		
		
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** PAUSED **");			
		wrefresh(vdata->right_window);
		while (vdata->key != 32)				
			key_listener(vdata, game, champs);
		vdata->paused = 0;

	}


	if (vdata->paused == 0 && !vdata->vasya)
	{
		mvwprintw(vdata->right_window, 1, START_X, "%s", "** RUNNING **");			
		wrefresh(vdata->right_window);
	}	

	key_listener(vdata, game, champs);
	if (vdata->key == 32)
	{		
		vdata->paused = 1;
		vdata->key = 0;
	}
}
