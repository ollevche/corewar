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
	id = get_value_by_arg(game, DIR_CODE, PC, 1);
	arg_champ = get_champ_by_id(head, id);
	if (arg_champ)
	{
		LAST_ALIVE = arg_champ;
		LAST_ALIVE->period_lives++;
		if (!game->arg->is_visual && !game->arg->log)
			ft_printf("A process shows that player %d (%s) is alive\n",
										LAST_ALIVE->id, LAST_ALIVE->name);
	}
	PERIOD_LIVES++;
	update_position(carry, 5);
	return (true);
}
