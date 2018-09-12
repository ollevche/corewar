/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	live(t_session *game, t_carry *carry, t_champ *head)
{
	int		id;
	t_champ	*arg_champ;

	LAST_LIVE = CYCLE;
	LAST_ALIVE = get_champ_by_id(head, REGS[0]);
	LAST_ALIVE->period_lives++;
	PERIOD_LIVES++;
	id = get_value_by_arg(game, DIR_CODE, PC, 1);
	arg_champ = get_champ_by_id(head, id);
	if (arg_champ)
	{
		LAST_ALIVE = arg_champ;
		LAST_ALIVE->period_lives++;
		PERIOD_LIVES++;
		if (!game->arg->is_visual && !game->arg->log)
			printf("A process shows that player %s is alive\n",LAST_ALIVE->name);
	}
	update_position(carry, 5);
	return (true);
}
