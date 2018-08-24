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
	int 	args[2][3 + 1];
	int		lpc;
	short	del_me_pls;

	(void)head;
	lpc = PC;
	ft_bzero((int**)args, 8 * sizeof(int));
	args[0][2] = -1;
	CHK_MV(set_arg_values(args, &lpc, game, 3));
	if (IS_REG(VAL1))
	{
		del_me_pls = VAL2;
		if (TYP2 == IND_CODE)
			write_to_map(game, PC + (del_me_pls % IDX_MOD), REGS[VAL1 - 1]);
		else if (IS_REG(VAL2))
			REGS[VAL2 - 1] = REGS[VAL1 - 1];
	}
	update_position(game, carry, JMP + 1);
	return (true);
}
