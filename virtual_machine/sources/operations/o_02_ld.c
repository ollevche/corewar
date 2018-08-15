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
	int 	args[2][2 + 1];
	int		lpc;

	lpc = PC;
	ft_bzero(args, 6 * sizeof(int));
	args[0][3] = -1;
	// Если первый аргумент T_IND, то сначала T_IND перезаписывается на T_IND % IDX_MOD,
	// а потом идём на ячейку, от текущей позиции + это значение, с той позиции считываем 4 байта -> idx_mod = true
	get_arg_values(args, &lpc, game, true);
	if (IS_REG(VAL2))
		REGS[VAL2 - 1] = VAL1; // записываем в T_REG
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL2));
}
