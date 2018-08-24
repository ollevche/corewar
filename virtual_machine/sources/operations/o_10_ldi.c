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
	CHK_MV(set_arg_values(args, &lpc, game, 10));
	if (IS_REG(VAL3))
	{
		if (TYP1 == REG_CODE)
			RET_CHECK(check_reg(&VAL1, game, carry, JMP), false);
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, game, carry, JMP), false);
		p = ((VAL1 + VAL2) % IDX_MOD) + PC;
		REGS[VAL3 - 1] =
		ft_byte_to_uint(MAPVAL(p, 1), MAPVAL(p, 2), MAPVAL(p, 3), MAPVAL(p, 4));
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, JMP + 1);
	return (IS_REG(VAL3));
}
