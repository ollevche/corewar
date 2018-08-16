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
	int 	args[2][2 + 1]; // TODO: check (is it wrong size or last elem?)
	int		lpc;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 6 * sizeof(int));
	args[0][2] = -1;
	set_arg_values((int**)args, &lpc, game, false);
	if (IS_REG(VAL1))
	{
		// Значение T_REG (первый аргумент) записывается:
		if (TYP2 == T_IND) // Если второй аргумент T_IND
			MAP[PC + (VAL2 % IDX_MOD)] = REGS[VAL1 - 1]; // то в ячейку, по адресу (текущая позиция PC плюс (T_IND % IDX_MOD))
		else if (IS_REG(VAL2))
			REGS[VAL2 = 1] = REGS[VAL1 - 1]; // Если второй аргумент T_REG - то в регистр, по этому номеру
	}
	update_position(game, carry, lpc + 1);
	return (true);
}
