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

static void	control_game_flow(t_session *game, t_champ *champs)
{
	t_uint		last_periods;
	t_process	*carry_iter;

	last_periods = (game->cycle - game->last_ctd) / game->cycle_to_die;
	// if it's a new period // first cycle (0) is a new period too
	if ((game->cycle - game->last_ctd) % game->cycle_to_die == 0)
	{
		while (champs)
		{
			carry_iter = champs->carrys;
			while (carry_iter)
			{
				// if (carry_iter->last_live < game->cycle - game->cycle_to_die)
				// 	del_process(&(champs->carrys), carry_iter); // TODO: this
				carry_iter = carry_iter->next;
			}
			champs = champs->next;
		}
		if (game->period_lives >= NBR_LIVE || last_periods == MAX_CHECKS)
			game->cycle_to_die -= CYCLE_DELTA;
		game->period_lives = 0;
	}
}

void		execute_processes(t_session *game, t_champ *champs)
{
	t_process	*carry_iter;

	while (champs)
	{
		carry_iter = champs->carrys;
		while (carry_iter)
		{
			if (carry_iter->inactive == 0)
			{
				if (carry_iter->op_code >= 1 && carry_iter->op_code <= 16)
				{
					// array function call // func_arr[carry_iter->op_code](args);
				}
				else
					update_position(carry_iter);
			}
			else
				carry_iter->inactive--;
			carry_iter = carry_iter->next;
		}
		champs = champs->next;
	}
}

void		display_map(t_session *game) // DEL or optimize
{
	t_uint	iter;
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

t_champ		*play_the_game(t_champ *champs)
{
	t_session	*game;
	t_champ		*winner;

	RET_CHECK(prepare(champs, &game), NULL)
	//	game->period_lives should be equal to total_champs initially
	while (game->period_lives && game->cycle_to_die >= 0)
	{
		void (*ptr[1]) (t_session*);
		
		ptr[0] = display_map;
		// display_map(game); // DEL
		ptr[0](game);
		// executes commands of processes
		// execute_processes(game, champs);
		game->cycle++;
		// updates [ lives / cycle_to_die / other game states ]
		control_game_flow(game, champs);
		ft_printf("%u\n", game->cycle); // DEL
	}  
	free_game(&game);
	winner = game->last_alive;
	return (winner);
}
