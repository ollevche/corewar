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

// TODO: check all new_X funcs for valid initial values

static void	control_game_flow(t_session *game, t_champ *champs)
{
	uint	last_periods;

	last_periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	// if it's a new period
	if ((game->cycle - game->last_ctd) % game->cycle_to_die == 0)
	{
		if (game->period_lives >= NBR_LIVE || last_periods == MAX_CHECKS)
			game->cycle_to_die -= CYCLE_DELTA;
		game->period_lives = 0;
	}
}

t_champ		*play_the_game(t_champ *champs)
{
	t_session	*game;

	RET_CHECK(prepare(champs, &game), NULL)
	//	game->period_lives should be equal to total_champs initially
	while (game->period_lives)
	{
		// updates [ lives / cycle_to_die / other game states ]
		control_game_flow(game, champs);
		// executes commands of processes
		execute_processes(game, champs);
		game->cycle++;
	}
	free_game(game);
	// picks an alive champ
	return (pick_winner(champs));
	// return (champs); // DEL
}
