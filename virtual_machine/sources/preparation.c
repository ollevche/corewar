/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:24:58 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/23 16:24:58 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

/*
**	creates processes for each champ
**	sets first reg to champ_id
*/

static t_uint	prepare_champs(t_champ *champs)
{
	t_uint champ_id;

	champ_id = 0;
	while (champs)
	{
		champ_id++; //	check it
		champs->id = champ_id;
		RET_CHECK(new_carry(&(champs->carrys), champ_id), 0);
		champs = champs->next;
	}
	return (champ_id);
}

/*
**	allocates mem for t_session and sets def values
**	filles t_session->map with 0 and sets champs code
**	sets t_process->pc to valid place in map
*/

static bool		prepare_session(t_session **gameptr, t_uint n)
{
	t_session	*game;

	*gameptr = (t_session*)malloc(sizeof(t_session));
	RET_CHECK(*gameptr, false);
	game = *gameptr;
	ft_memset(game->map, 0, MEM_SIZE);
	game->cycle = 0;
	game->period_lives = n;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->last_ctd = 0;
	game->total_champs = n;
	return (true);
}

static void		place_code(t_champ *champs, t_session *game)
{
	t_uint	gap;
	t_uint	champ_mark;

	gap = MEM_SIZE / game->total_champs;
	champ_mark = 0;
	while (champs)
	{
		ft_memcpy(game->map + champ_mark, champs->code, champs->code_len);
		champs->carrys->pc = champ_mark;
		champ_mark += gap;
		champs = champs->next;
	}
}

bool			prepare(t_champ *champs, t_session **game)
{
	t_uint	champs_n;

	champs_n = prepare_champs(champs);
	RET_CHECK(champs_n, false);
	if (champs_n > MAX_PLAYERS)
	{
		ft_printf("Too many champions\n"); // should we move this to validation stage?
		return (false);
	}
	RET_CHECK(prepare_session(game, champs_n), NULL);
	//	places champs code at the game->map
	place_code(champs, *game);
	// display_map(*game); // DEL
	return (true);
}