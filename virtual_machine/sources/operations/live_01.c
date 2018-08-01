/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	live(t_session *game, t_champ *champ, t_process *carry, t_champ *head)
{
	t_uint	id;
	t_champ	*arg_champ;
	t_uchar *map;
	t_uint	pc;

	carry->last_live = game->cycle;
	game->last_alive = champ;
	game->period_lives++;
	map = game->map;
	pc = carry->pc;
	id = ft_byte_to_uint(map[pc + 1], map[pc + 2], map[pc + 3], map[pc + 4]);
	arg_champ = get_champ_by_id(head, id);
	if (arg_champ)
	{
		game->last_alive = arg_champ;
		game->period_lives++;
	}
	update_position(game, carry, 5);
	return (true);
}