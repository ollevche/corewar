/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
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
**	returns total number of champs
*/

static int	count_champs(t_champ *champs)
{
	int champs_count;

	champs_count = 0;
	while (champs)
	{
		champs_count++;
		champs = champs->next;
	}
	return (champs_count);
}

/*
**	allocates mem for t_session and sets def values
*/

static bool	prepare_session(t_session **gameptr, int n)
{
	t_session	*game;

	*gameptr = (t_session*)malloc(sizeof(t_session));
	RET_CHECK(*gameptr, false);
	game = *gameptr;
	ft_memset(game->map, 0, MEM_SIZE);
	game->cycle = 0;
	game->period_lives = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->last_ctd = 0;
	game->last_alive = NULL;
	game->carrys = NULL;
	game->total_champs = n;
	game->carry_num = n;
	return (true);
}

/*
**	puts the code of champs on the map
**	chooses code positions based on champ number
**	sets carries pc to start positions (first byte of champ code)
*/

static bool	place_code(t_champ *champs, t_session *game)
{
	int			gap;
	int			champ_mark;

	gap = MEM_SIZE / game->total_champs;
	champ_mark = 0;
	while (champs)
	{
		ft_memcpy(game->map + champ_mark, champs->code, champs->code_len);
		RET_CHECK(new_carry(&(game->carrys), champs->id), false);
		// game->carrys->champ = champs->id; champs fix
		game->carrys->pc = champ_mark;
		update_position(game, game->carrys, 0);
		champ_mark += gap;
		champs = champs->next;
	}
	return (true);
}

bool		prepare(t_champ *champs, t_session **game)
{
	int	champs_n;

	champs_n = count_champs(champs);
	if (champs_n > MAX_PLAYERS)
	{
		ft_printf("Too many champions\n"); // TODO: print this before visualization
		return (false);
	}
	RET_CHECK(prepare_session(game, champs_n), NULL);
	place_code(champs, *game);
	return (true);
}
