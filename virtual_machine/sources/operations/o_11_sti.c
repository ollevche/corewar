/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:57:21 by dpozinen          #+#    #+#             */
/*   Updated: 2018/09/07 12:57:22 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	sti(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;
	int		p;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][3] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 11));
	if (IS_REG(VAL1))
	{
		if (TYP2 == REG_CODE)
			RET_CHECK(check_reg(&VAL2, carry, JMP), false);
		if (TYP3 == REG_CODE)
			RET_CHECK(check_reg(&VAL3, carry, JMP), false);
		p = PC + (VAL2 + VAL3) % IDX_MOD;
		write_to_map(game, p, REGS[VAL1 - 1], carry->champ);
	}
	update_position(carry, JMP + 1);
	return (true);
}
