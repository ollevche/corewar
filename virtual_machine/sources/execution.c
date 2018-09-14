/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:17:39 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/26 13:17:39 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

/*
**	inits an array of functions which represents possible operations ▽
*/

static void	init_operations(t_operation operations[OP_COUNT + 2])
{
	operations[0] = NULL;
	operations[1] = live;
	operations[2] = ld;
	operations[3] = st;
	operations[4] = add;
	operations[5] = sub;
	operations[6] = and;
	operations[7] = or;
	operations[8] = xor;
	operations[9] = zjmp;
	operations[10] = ldi;
	operations[11] = sti;
	operations[12] = op_fork;
	operations[13] = lld;
	operations[14] = lldi;
	operations[15] = op_lfork;
	operations[16] = aff;
	operations[17] = NULL;
}

/*
** TODO: game has arg pointer now (refactor old code)
*/

static void	perform_operation(t_session *game, t_champ *champs, t_carry *carry,
									t_operation operations[OP_COUNT + 2])
{
	int		prev_pc;
	bool	is_valid;

	prev_pc = carry->pc;
	is_valid = carry->op_code != 9 || !carry->carry;
	operations[carry->op_code](game, carry, champs);
	if (is_valid && game->arg->log)
		log_operation(game, carry->pc, prev_pc);
	carry->op_code = DEF_OPCODE;
}

/*
**	executes all of the carries, which is active ▽
**	or decrease inactive counter (if inactive)
*/

void		execute_carries(t_session *game, t_champ *champs)
{
	t_carry		*icarry;
	t_operation	operations[OP_COUNT + 2];

	init_operations(operations);
	icarry = game->carries;
	while (icarry)
	{
		if (icarry->op_code >= 1 && icarry->op_code <= OP_COUNT)
		{
			if (icarry->inactive == 0)
				perform_operation(game, champs, icarry, operations);
			else
				icarry->inactive--;
		}
		else
		{
			update_opcode(game, icarry);
			if (icarry->op_code == DEF_OPCODE)
				update_position(icarry, 1);
		}
		icarry = icarry->next;
	}
}
