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
	short	dir;
	int		lpc;

	(void)head;
	lpc = PC;
	dir = ft_byte_to_uint(0, 0, MAP[PC + 1], MAP[PC + 2]);
	lpc = move_pc(lpc, 2);
	if (CARRY)
		update_position(game, carry, dir % IDX_MOD);
	else
		update_position(game, carry, JMP + 1);
	return (CARRY);
}
