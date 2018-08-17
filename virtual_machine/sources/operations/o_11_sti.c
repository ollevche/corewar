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
	set_arg_values(args, &lpc, game, 11);
	if (IS_REG(VAL1))
	{
		RET_CHECK(TYP2 == T_REG && check_reg(&VAL2, game, carry, lpc), false);
		RET_CHECK(TYP3 == T_REG && check_reg(&VAL3, game, carry, lpc), false);
		MAP[PC + ((VAL2 + VAL3) % IDX_MOD)] = REGS[VAL1 - 1];
	}
	update_position(game, carry, lpc + 1);
	return (true);
}
