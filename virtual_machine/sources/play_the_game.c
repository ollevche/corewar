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

t_champ			*play_the_game(t_champ *champs)
{
	t_session	*game;

	RET_CHECK(prepare(champs, &game), NULL)
	// // while lives or it's first cycle_to_die execution
	// while (game->cycle < game->cycle_to_die || game->period_lives)
	// {
	// 	// updates [ lives / cycle_to_die / other game states ]
	// 	control_game_flow(game, champs);
	// 	// executes commands of processes
	// 	execute_processes(game, champs);
	// }
	// free_game(game);
	// // picks an alive champ
	// return (pick_winner(champs));
	return (champs); // DEL
}
