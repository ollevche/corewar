/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_14_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:42:41 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/15 15:42:41 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	lldi(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;
	int		p;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 14));
	if (IS_REG(VAL3))
	{
		if (TYP1 == REG_CODE)
			RET_CHECK(check_reg(&VAL1, carry, JMP), false);
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, carry, JMP), false);
		p = VAL1 + VAL2 + PC;
		REGS[VAL3 - 1] = // 3 lines for one operation. the fuck is this. TODO: Rewrite ft_byte_to_int? (81 character)
		ft_byte_to_uint(MAPVAL(p, 0), MAPVAL(p, 1), MAPVAL(p, 2),
																MAPVAL(p, 3));
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false); // NOTE: it can be incorrect; test it
	}
	update_position(carry, JMP + 1);
	return (IS_REG(VAL3));
}
