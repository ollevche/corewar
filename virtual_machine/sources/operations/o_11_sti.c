/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

static void write_to_map(t_session *game, int pos, int value) // TODO: remove 2 write_to_map funcs
{
	MAP[pos + 0] = (value & -16777216) >> 24;
	MAP[pos + 1] = (value & 16711680) >> 16;
	MAP[pos + 2] = (value & 65280) >> 8;
	MAP[pos + 3] = value & 255;
}

bool	sti(t_session *game, t_carry *carry, t_champ *head)
{
	int 	args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	RET_CHECK(set_arg_values(args, &lpc, game, 11), false);
	if (IS_REG(VAL1))
	{
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, game, carry, JMP), false);
		if (TYP3 == REG_CODE)
			RET_CHECK(check_reg(&VAL3, game, carry, JMP), false);
		write_to_map(game, PC + (VAL2 + VAL3) % IDX_MOD, REGS[VAL1 - 1]);
	}
	update_position(game, carry, JMP + 1);
	return (true);
}
