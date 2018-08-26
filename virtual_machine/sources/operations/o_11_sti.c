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

bool	sti(t_session *game, t_carry *carry, t_champ *head)
{
	int 	args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 11));
	if (IS_REG(VAL1))
	{
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, game, carry, JMP), false);
		if (TYP3 == REG_CODE)
			RET_CHECK(check_reg(&VAL3, game, carry, JMP), false);
		write_to_map(game, PC + (VAL2 + VAL3) % IDX_MOD, REGS[VAL1 - 1], REGS[0]);
	}
	update_position(game, carry, JMP + 1);
	return (true);
}
