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
**	inits an array of functions which represents possible operations
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

int			move_pc(int pc, int val)
{
	pc += val;
	if (pc >= MEM_SIZE)
		pc %= MEM_SIZE;
	else if (pc < 0)
		pc = MEM_SIZE + pc; // pc is neg so it has to be +
	return (pc);
}

/*
**	moves a pc of the carry to specified position (to right/left from the pc by val bytes)
**	sets op_code to pc internal value (op_code of the new position)
**	sets inactive counter to operation execution time (in cycles)
*/

void		update_position(t_session *game, t_carry *carry, int val)
{
	carry->pc = move_pc(carry->pc, val);
	carry->op_code = game->map[carry->pc];
	if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
		carry->inactive = g_optab[carry->op_code].cycles - 1;
}

/*
**	executes all of the carries, which is active
**	or decrease inactive counter (if inactive)
*/

void		execute_carries(t_session *game, t_champ *champs)
{
	t_carry	*icarry;
	t_operation operations[OP_COUNT + 2]; // static?

	init_operations(operations);
	icarry = game->carries;
	while (icarry)
	{
		if (icarry->inactive == 0)
		{
			if (icarry->op_code >= 1 && icarry->op_code <= OP_COUNT)
				operations[icarry->op_code](game, icarry, champs);
			else
				update_position(game, icarry, 1);
		}
		else
			icarry->inactive--;
		icarry = icarry->next;
	}
}
