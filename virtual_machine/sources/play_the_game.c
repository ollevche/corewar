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

static int	kill_processes(t_champ *champs, int period_start)
{
	t_process	*icarry;
	int			killed;

	killed = 0;
	while (champs)
	{
		icarry = champs->carrys;
		while (icarry)
		{
			if (icarry->last_live < period_start)
			{
				del_process(&(champs->carrys), icarry);
				killed++;
			}
			icarry = icarry->next;
		}
		champs = champs->next;
	}
	return (killed);
}

static void	control_game_flow(t_session *game, t_champ *champs)
{
	int	periods; // since last cycle_to_die change
	int	cycles; // in current period
	int	killed;

	periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	cycles = game->cycle - game->last_ctd - game->cycle_to_die * periods;
	if (cycles == 0) // it's start of the period
	{
		killed = kill_processes(champs, game->cycle - game->cycle_to_die);
		game->process_num -= killed;
		if (game->period_lives >= NBR_LIVE || periods == MAX_CHECKS)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			game->last_ctd = game->cycle;
		}
		game->period_lives = 0;
	}
}

static void	log(t_session *game, t_champ *champs)
{
	t_champ		*ichamp;
	t_process	*icarry;

	ft_printf("--- --- --- --- --- --- --- --- ---\n");	
	ft_printf("cycle: %d\n", game->cycle);
	ft_printf("period lives: %d\n", game->period_lives);
	ft_printf("cycle to die: %d\n", game->cycle_to_die);
	ft_printf("last 'cycle to die' change: %d\n", game->last_ctd);
	ft_printf("carrys positions:\n");
	ichamp = champs;
	while (ichamp)
	{
		ft_printf("\tchamp %d:", ichamp->id);
		icarry = ichamp->carrys;
		while (icarry)
		{
			ft_printf(" %d", icarry->pc);
			icarry = icarry->next;
		}
		ft_printf("\n");
		ichamp = ichamp->next;
	}
	if (game->last_alive)
		ft_printf("last alive champ: %d\n", game->last_alive->id);
}

t_champ		*play_the_game(t_champ *champs)
{
	t_session	*game;
	t_champ		*winner;

	RET_CHECK(prepare(champs, &game), NULL)
	//	game->period_lives should be equal to total_champs initially
	while (game->process_num > 0 && game->cycle_to_die >= 0)
	{
		log(game, champs); // DEL
		// executes commands of processes
		execute_processes(game, champs);
		game->cycle++;
		// updates [ lives / cycle_to_die / other game states ]
		control_game_flow(game, champs);
	}  
	free_session(&game);
	winner = game->last_alive;
	return (winner);
}
