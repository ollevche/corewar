/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_06_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	and(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][3] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 6));
	if (IS_REG(VAL3))
	{
		if (TYP1 == REG_CODE)
			RET_CHECK(check_reg(&VAL1, carry, JMP), false);
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, carry, JMP), false);
		REGS[VAL3 - 1] = VAL1 & VAL2;
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(carry, JMP + 1);
	return (IS_REG(VAL3));
}
