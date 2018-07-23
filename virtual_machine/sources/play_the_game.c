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

/*
**	creates processes for each champ
**	sets first reg to champ_id
*/

static bool	prepare_champs(t_champ *champs)
{
	t_uint champ_id;

	champ_id = 0;
	while (champs->next)
	{
		champ_id++; //	check it
		champs->id = champ_id;
		RET_CHECK(new_carry(&(champs->carrys), champ_id), false);
	}
	return (true);
}

/*
**	allocates mem for t_session and sets def values
**	filles t_session->map with 0 and sets champs code
**	sets t_process->pc to valid place in map
*/

static bool	prepare_session(t_session **game_ptr, t_champ *champs)
{
	t_session	*game;

	*game_ptr = (t_session*)malloc(sizeof(t_session));
	RET_CHECK(*game_ptr, false);
	game = *game_ptr;
	game->cycle = 0;
	game->period_lives = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
	//	TODO: placing code at the game->map
	ft_memset(game->map, 0, MEM_SIZE); // check it
	//	need players count :(
	return (true);
}

t_champ		*play_the_game(t_champ *champs)
{
	t_session	*game;

	//	allocates mem for champs carrys and sets r1 registry in each one 
	RET_CHECK(prepare_champs(champs), NULL);
	//	allocates mem for a game session
	//	places champs code at the game->map and etc
	RET_CHECK(prepare_session(&game, champs), NULL);
	//	while lives or it's first cycle_to_die execution
	while (game->cycle < game->cycle_to_die || game->period_lives)
	{
		//	updates [ lives / cycle_to_die / other game states ]
		control_game_flow(game, champs);
		//	executes commands of processes
		execute_processes(game, champs);
	}
	free_game(game);
	//	picks an alive champ
	return (pick_winner(champs));
}
