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

// TODO: define lines like game->last_alive / carry->last_live / etc
// TODO: print "A process shows that player X (champion_name) is alive"

bool	live(t_session *game, t_carry *carry, t_champ *head)
{
	t_uint	id;
	t_champ	*arg_champ;

	LAST_LIVE = CYCLE;
	LAST_ALIVE = get_champ_by_id(head, REGS[0]);
	PERIOD_LIVES++;
	ft_printf("A process shows that player %s is alive\n", LAST_ALIVE->name);
	id = ft_byte_to_uint(MAP[PC + 1], MAP[PC + 2], MAP[PC + 3], MAP[PC + 4]);
	arg_champ = get_champ_by_id(head, id);
	if (arg_champ)
	{
		LAST_ALIVE = arg_champ;
		PERIOD_LIVES++;
		ft_printf("A process shows that player %s is alive\n", LAST_ALIVE->name);
	}
	update_position(game, carry, 5);
	return (true);
}
