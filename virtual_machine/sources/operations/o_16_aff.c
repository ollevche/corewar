/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	aff(t_session *game, t_carry *carry, t_champ *head)
{
	int		args[2][3 + 1];
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][1] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 16));
	if (IS_REG(VAL1) && !game->arg->is_visual && !game->arg->log)
		ft_printf("aff output: %c\n", REGS[VAL1 - 1] % 256);
	update_position(carry, JMP + 1);
	return (IS_REG(VAL1));
}
