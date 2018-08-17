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
	int 	args[2][3 + 1];
	int		lpc;
	int		p;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	set_arg_values(args, &lpc, game, 14);
	if (IS_REG(VAL3))
	{
		RET_CHECK(TYP1 == T_REG && check_reg(&VAL1, game, carry, JMP), false);
		RET_CHECK(TYP2 == T_REG && check_reg(&VAL2, game, carry, JMP), false);
		p = VAL1 + VAL2 + PC;
		REGS[VAL3] =
			ft_byte_to_uint(MAP[p + 1], MAP[p + 2], MAP[p + 3], MAP[p + 4]);
		CARRY = (REGS[VAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, JMP + 1);
	return (IS_REG(VAL3));
}
