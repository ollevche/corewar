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

	periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	cycles = game->cycle - game->last_ctd - game->cycle_to_die * periods;
	if (cycles == 0) // it's start of the period
	{
		killed = kill_carries(&(game->carries), game->cycle - game->cycle_to_die);
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

// static void	log(t_session *game, bool is_log)
// {
// 	t_carry	*icarry;

// 	if (!is_log)
// 		return ;
// 	ft_printf("--- --- --- --- --- --- --- --- ---\n");
// 	ft_printf("cycle: %d\n", game->cycle);
// 	ft_printf("period lives: %d\n", game->period_lives);
// 	ft_printf("cycle to die: %d\n", game->cycle_to_die);
// 	ft_printf("last 'cycle to die' change: %d\n", game->last_ctd);
// 	ft_printf("total carries: %d\n", game->carry_num);
// 	ft_printf("carries positions (champ - pos - last_live - inactive - map bytes):\n");
// 	icarry = game->carries;
// 	while (icarry)
// 	{
// 		ft_printf("%d\t%d\t%d\t%d\t%02x %02x %02x %02x\n", icarry->regs[0], icarry->pc, icarry->last_live, icarry->inactive,
// 			game->map[move_pc(icarry->pc, -1)], game->map[icarry->pc], game->map[move_pc(icarry->pc, 1)], game->map[move_pc(icarry->pc, 2)]);
// 		icarry = icarry->next;
// 	}
// 	if (game->last_alive)
// 		ft_printf("last alive champ: %d\n", game->last_alive->id);
// }

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
	RET_CHECK(prepare(champs, &game), NULL); // TODO: data should be prepared before visu_init call
	visu_drawing(&vdata, game, champs, arg); // TODO: visu_init should call visu_drawing on prepared data
	game->cycle++; // TODO: remove this line
	winner = get_last_champ(champs);
	while (game->carry_num > 0 && game->cycle_to_die >= 0
			&& !is_dump(game, arg))
	{
		control_game_flow(game, champs);
		game->cycle++;
		log_cycles(game, arg);
		execute_carries(game, champs);
		visu_drawing(&vdata, game, champs, arg);
	}
	free_session(&game);
	winner = game->last_alive ? game->last_alive : winner;
	visu_finalizing(&vdata, game, champs, arg);
	return (winner);
}
