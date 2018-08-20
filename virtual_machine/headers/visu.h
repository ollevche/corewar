/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:43:06 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/16 15:43:07 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <unistd.h>
# include "vm.h"

# define W_HEIGHT 68
# define W_WIDTH 251
# define START_X 2
# define CARRY_COLOR_PAIR 100


typedef struct				s_name
{
	WINDOW					*n_window;
	char					*full_name;
	char					*displayed_name;
	char					*hidden_name;
	int						hidden_len;
	struct s_name			*next;
}							t_name;



typedef struct				s_vdata
{
	WINDOW					*left_window;
	WINDOW					*right_window;
	int						key;
	int 					paused;
	unsigned long long		sec;
	t_name					*animated_names;
}							t_vdata;

void    					show_right(t_vdata *vdata, t_session *game, t_champ *champs);
void						show_left(WINDOW *left_window, t_session *game, t_champ *champs);
int							visu_initializing	(t_vdata *vdata, t_arg *arg);
int							visu_finalizing		(t_vdata *vdata, t_arg *arg);
int							visu_drawing(t_vdata *vdata, t_session *game, t_champ *champs,t_arg *arg);
void						show_players(WINDOW *nbr_win, t_champ *champs, int *i);
int							is_carry(t_carry *carrys, int index);

void						playback_controls(t_vdata *vdata);


#endif
