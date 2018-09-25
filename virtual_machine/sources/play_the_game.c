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
**	int	periods; // since last cycle_to_die change
**	int	cycles; // in current period
*/

static void	control_game_flow(t_session *game, t_champ *champs)
{
	int	periods;
	int	cycles;
	int	killed;
	int	period_start;

	periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	cycles = game->cycle - game->last_ctd - game->cycle_to_die * periods;
	if (cycles == 0)
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
	bool		game_over;

	RET_CHECK(prepare(champs, &game, arg), NULL);
	winner = get_last_champ(champs);
	game_over = false;
	while (!game_over)
	{
		if (!visualizing(&vdata, game, champs, arg))
			break ;
		game_over = game->carry_num < 1 || game->cycle_to_die < 0;
		log_cycles(game, arg, game_over);
		execute_carries(game, champs);
		control_game_flow(game, champs);
		game->cycle++;
		if (is_dump(game, arg))
			break ;
	}
	winner = game->last_alive ? game->last_alive : winner;
	free_session(&game);
	return (winner);
}
