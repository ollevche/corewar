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

static void	prepare_spot_map(t_champ *champs, t_session *game)
{
	int		def_value;
	bool	def_value_found;
	t_champ	*iter;

	def_value = 0;
	def_value_found = false;
	while (!def_value_found)
	{
		iter = champs;
		while (iter)
		{
			if (iter->id == def_value)
			{
				def_value++;
				break ;
			}
			iter = iter->next;
		}
		if (!iter)
			def_value_found = true;
	}
	ft_intset(game->spot_map, def_value, MEM_SIZE);
}

/*
**	allocates mem for t_session and sets def values
*/

static bool	prepare_session(t_session **gameptr, int n, t_arg *arg)
{
	t_session	*game;

	*gameptr = (t_session*)malloc(sizeof(t_session));
	RET_CHECK(*gameptr, false);
	game = *gameptr;
	ft_memset(game->map, 0, MEM_SIZE);
	game->cycle = 1;
	game->period_lives = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->last_ctd = 0;
	game->last_alive = NULL;
	game->carries = NULL;
	game->carry_num = n;
	game->total_champs = n;
	game->arg = arg;
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
		ft_intset(game->spot_map + champ_mark, champs->id, champs->code_len);
		RET_CHECK(new_carry(&(game->carries), champs->id), false);
		game->carries->pc = champ_mark;
		update_opcode(game, game->carries);
		game->carries->inactive++;
		champ_mark += gap;
		champs = champs->next;
	}
	return (true);
}

bool		prepare(t_champ *champs, t_session **game, t_arg *arg)
{
	int	champs_n;

	champs_n = count_champs(champs);
	RET_CHECK(prepare_session(game, champs_n, arg), NULL);
	prepare_spot_map(champs, *game);
	place_code(champs, *game);
	return (true);
}
