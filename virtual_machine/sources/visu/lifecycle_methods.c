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
#include "vm_funcs.h"

static int	visu_initializing(
	t_vdata *vdata, t_arg *arg, t_champ *champs, t_session *game)
{
	if (game->cycle != 1)
		return (-1);
	if (!initscr())
		return (0);
	raw();
	default_settings(vdata, arg, champs, game);
	init_color(COLOR_WHITE, 400, 400, 400);
	scrolling_controls(vdata, 69, 197);
	live_bars_initializing(vdata, champs, 67, 33);
	author_line_initializing(vdata);
	console_initializing(vdata);
	return (1);
}

static void	input_cycle_loading(t_vdata *vdata)
{
	char		*cycles;
	static int	show_cycles = true;

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
			cycles = ft_itoa(vdata->game->cycle);
			show_cycles = true;
			show_alert_window(vdata, "     Loading... Press [ESC] to abort!",
				show_cycles ? cycles : "The window is rendered only ONCE");
			ft_strdel(&cycles);
		}
	}
}

int			visualizing(
	t_vdata *vdata, t_session *game, t_champ *champs, t_arg *arg)
{
	if (!arg->is_visual)
		return (1);
	if (!visu_initializing(vdata, arg, champs, game))
		return (0);
	input_cycle_loading(vdata);
	if (game->cycle == vdata->input_cycle)
		vdata->input_cycle = 0;
	if (!vdata->input_cycle)
	{
		show_left(vdata, game, champs);
		show_right(vdata, game, champs);
		players_line_refresh(vdata);
		refresh_live_bars(vdata, FALSE);
		if (playback_controls(vdata, game, champs) != 0)
			return (0);
	}
	if (game->carry_num <= 0 || game->cycle_to_die < 0)
	{
		if (gameover_window(vdata, game, champs) != 0)
			return (0);
	}
	return (1);
}

int			visu_finalizing(t_vdata *vdata, t_arg *arg)
{
	if (vdata == NULL || arg == NULL || !arg->is_visual)
		return (1);
	if (vdata->music == 1)
		system("killall afplay");
	console_finalizing(vdata);
	scrolling_finalizing(vdata);
	live_bars_finalizing(vdata);
	delwin(vdata->left_window);
	delwin(vdata->right_window);
	delwin(vdata->alert_window);
	delwin(vdata->input_window);
	endwin();
	vdata = NULL;
	return (0);
}
