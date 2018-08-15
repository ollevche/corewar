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
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (3 + 1)), false);
	arg_types[3] = -1;
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, false)))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	if (IS_REG(VAL3))
	{
		if (TYP1 == T_REG && !check_reg(&VAL1, game, carry, lpc))
			return (false);
		if (TYP2 == T_REG && !check_reg(&VAL2, game, carry, lpc))
			return (false);
		REGS[VAL3 - 1] = VAL1 ^ VAL2;
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL3));
}
