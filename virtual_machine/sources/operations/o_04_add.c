/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_04_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:41:31 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/08 13:41:32 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	add(t_session *game, t_carry *carry, t_champ *head)
{
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (2 + 1)), false);
	arg_types[2] = -1;
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, false)))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	if (!IS_REG(AVAL1) || !IS_REG(AVAL2) || !IS_REG(AVAL3))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	REGS[AVAL3 - 1] = REGS[AVAL1 - 1] + REGS[AVAL2 - 1];
	CARRY = (REGS[AVAL3 - 1] == 0 ? true : false);
	update_position(game, carry, lpc + 1);
	return (true);
}
