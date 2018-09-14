/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	lld(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][2] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 13));
	update_position(carry, JMP + 1);
	if (!IS_REG(VAL2))
		return (false);
	REGS[VAL2 - 1] = VAL1;
	CARRY = (REGS[VAL2 - 1] == 0 ? true : false);
	return (IS_REG(VAL2));
}
