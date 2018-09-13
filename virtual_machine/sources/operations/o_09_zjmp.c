/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	zjmp(t_session *game, t_carry *carry, t_champ *head)
{
	int		lpc;
	short	dir;

	(void)head;
	lpc = PC;
	dir = ft_byte_to_uint(0, 0, MAPVAL(PC, 1), MAPVAL(PC, 2));
	lpc = move_pc(lpc, 2);
	if (CARRY)
		update_position(carry, dir % IDX_MOD);
	else
		update_position(carry, JMP + 1);
	return (true);
}
