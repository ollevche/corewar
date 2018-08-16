/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:19:17 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/14 15:19:17 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	ldi(t_session *game, t_carry *carry, t_champ *head)
{
	int 	args[2][3 + 1];
	int		lpc;
	int		p;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][3] = -1;
	set_arg_values(args, &lpc, game, false);
	if (IS_REG(VAL3))
	{
		RET_CHECK(TYP1 == T_REG && check_reg(&VAL1, game, carry, lpc), false);
		RET_CHECK(TYP2 == T_REG && check_reg(&VAL2, game, carry, lpc), false);
		p = ((VAL1 + VAL2) % IDX_MOD) + PC;
		REGS[VAL3] =
			ft_byte_to_uint(MAP[p + 1], MAP[p + 2], MAP[p + 3], MAP[p + 4]);
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL3));
}
