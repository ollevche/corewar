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
	int 	args[2][3 + 1];
	int		lpc;

	(void)head; // TODO: head is unused in a lot of ops
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][3] = -1;
	set_arg_values((int**)args, &lpc, game, false);
	if (IS_REG(VAL2))
		REGS[VAL2 - 1] = VAL1;
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL2));
}