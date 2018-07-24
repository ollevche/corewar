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

static uint	prepare_champs(t_champ *champs)
{
	uint champ_id;

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

static bool		prepare_session(t_session **gameptr, uint n) // TODO: modify it
{
	t_session	*game;

	*gameptr = (t_session*)malloc(sizeof(t_session));
	RET_CHECK(*gameptr, false);
	game = *gameptr;
	game->cycle = 0;
	game->period_lives = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->total_champs = n;
	ft_memset(game->map, 0, MEM_SIZE);
	return (true);
}

static void		place_code(t_champ *champs, t_session *game)
{
	uint	gap;
	uint	champ_mark;

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

void			display_map(t_session *game) // DEL or optimize
{
	uint	iter;
	t_uchar	*map;

	iter = 0;
	map = game->map;
	while (iter < MEM_SIZE)
	{
		if (iter % 64 == 0)
			ft_printf("0x%04x : ", iter);
		ft_printf("%02x ", map[iter]);
		iter++;
		if (iter % 64 == 0)
			ft_printf("\n");
	}
}

bool			prepare(t_champ *champs, t_session **game)
{
	uint	champs_n;

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
	display_map(*game); // DEL
	return (true);
}