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
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (2 + 1)), false);
	arg_types[2] = -1;
	// Если первый аргумент T_IND, то сначала T_IND перезаписывается на T_IND % IDX_MOD,
	// а потом идём на ячейку, от текущей позиции + это значение, с той позиции считываем 4 байта -> idx_mod = true
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, true)))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	if (IS_REG(AVAL2))
		REGS[AVAL2 - 1] = AVAL1; // записываем в T_REG
	update_position(game, carry, lpc + 1);
	return (IS_REG(AVAL2));
}
