/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:15:22 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/09 15:15:23 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	ld(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero(args, 8 * sizeof(int));
	args[0][2] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 2));
	update_position(carry, JMP + 1);
	if (!IS_REG(VAL2))
		return (true);
	REGS[VAL2 - 1] = VAL1;
	CARRY = (REGS[VAL2 - 1] == 0 ? true : false);
	return (true);
}
