/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_06_xor.c                                         :+:      :+:    :+:   */
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
	int 	args[2][3 + 1];
	int		lpc;

	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	set_arg_values(args, &lpc, game, false);
	if (IS_REG(VAL3))
	{
		RET_CHECK(TYP1 == T_REG && check_reg(&VAL1, game, carry, lpc), false);
		RET_CHECK(TYP1 == T_REG && check_reg(&VAL1, game, carry, lpc), false);
		REGS[VAL3 - 1] = VAL1 ^ VAL2;
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL3));
}
