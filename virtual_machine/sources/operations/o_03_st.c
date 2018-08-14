/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:24:35 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/10 14:24:36 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	st(t_session *game, t_carry *carry, t_champ *head)
{
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (2 + 1)), false);
	arg_types[2] = -1;
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, false)))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	if (IS_REG(AVAL1))
	{
		// Значение T_REG (первый аргумент) записывается:
		if (ATYP2 == T_IND) // Если второй аргумент T_IND
			MAP[PC + (AVAL2 % IDX_MOD)] = REGS[AVAL1 - 1]; // то в ячейку, по адресу (текущая позиция PC плюс (T_IND % IDX_MOD))
		else if (IS_REG(AVAL2))
			REGS[AVAL2 = 1] = REGS[AVAL1 - 1]; // Если второй аргумент T_REG - то в регистр, по этому номеру
	}
	update_position(game, carry, lpc + 1);
	return (true);
}
