/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_the_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:53:47 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/22 14:53:48 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"
#include "visu.h"

static int	kill_carries(t_carry **carries, int period_start)
{
	t_carry	*current;
	t_carry	*prev;
	int		killed;

	current = *carries;
	prev = NULL;
	killed = 0;
	while (current)
	{
		if (current->last_live <= period_start)
		{
			del_carry(carries, prev, current);
			if (prev)
				current = prev->next;
			else
				current = *carries;
			killed++;
			continue ;
		}
		prev = current;
		current = current->next;
	}
	return (killed);
}

/*
**	controls execution of the game by periods
**	(1) new period ->
**	(2) checking some params (NBR_LIVE, MAX_CHECKS, dead carries) ->
**	(3) setting params to correct values -> end
*/

static void	control_game_flow(t_session *game, t_champ *champs)
{
	int	periods; // since last cycle_to_die change
	int	cycles; // in current period
	int	killed;
	int	period_start;

	periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	cycles = game->cycle - game->last_ctd - game->cycle_to_die * periods;
	if (cycles == 0) // it's start of the period
	{
		period_start = game->cycle - game->cycle_to_die;
		killed = kill_carries(&(game->carries), period_start);
		game->carry_num -= killed;
		if (game->period_lives >= NBR_LIVE || periods == MAX_CHECKS)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			game->last_ctd = game->cycle;
		}
		game->period_lives = 0;
		while (champs)
		{
			champs->period_lives = 0;
			champs = champs->next;
		}
	}
}

static bool	is_dump(t_session *game, t_arg *arg)
{
	int		iter;
	t_uchar	*map;

	if (arg->is_visual || game->cycle <= arg->dump || arg->dump < 0)
		return (false);
	iter = 0;
	map = game->map;
	while (iter < MEM_SIZE)
	{
		if (iter % 64 == 0)
			ft_printf("\n0x%04x : ", iter);
		ft_printf("%02x ", map[iter]);
		iter++;
	}
	ft_printf("\n");
	return (true);
}

/*
**	main game loop: 1 cycle = 1 iteration
*/

t_champ		*play_the_game(t_champ *champs, t_arg *arg)
{
	t_session	*game;
	t_champ		*winner;
	t_vdata		vdata;

	RET_CHECK(visu_initializing(&vdata, arg, champs), NULL);
	RET_CHECK(prepare(champs, &game, arg), NULL);
	winner = get_last_champ(champs);
	while (game->carry_num > 0 && game->cycle_to_die >= 0
			&& !is_dump(game, arg))
	{
		log_cycles(game, arg);
		execute_carries(game, champs);
		control_game_flow(game, champs);
		if (visu_drawing(&vdata, game, champs, arg))
			break ;
		game->cycle++;
	}
	winner = game->last_alive ? game->last_alive : winner;
	free_session(&game);
	visu_finalizing(&vdata, arg);
	return (winner);
}
