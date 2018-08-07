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
	// operations[2] = load;
	// operations[3] = store;
	// operations[4] = addition;
	// operations[5] = soustraction;
	// operations[6] = and;
	// operations[7] = or;
	// operations[8] = xor;
	// operations[9] = zero_jump;
	// operations[10] = load_index;
	// operations[11] = store_index;
	// operations[12] = fork;
	// operations[13] = long_load;
	// operations[14] = long_load_index;
	// operations[15] = long_fork;
	// operations[16] = aff;
	operations[17] = NULL;
}

/*
**	moves a pc of the process to specified position (to right/left from the pc by val bytes)
**	sets op_code to pc internal value (op_code of the new position)
**	sets inactive counter to operation execution time (in cycles)
*/

void		update_position(t_session *game, t_process *carry, int val)
{
	carry->pc += val;
	if (carry->pc >= MEM_SIZE)
		carry->pc %= MEM_SIZE;
	else if (carry->pc < 0)
		carry->pc = MEM_SIZE + carry->pc; // carry->pc is neg so it has to be +
	carry->op_code = game->map[carry->pc];
	if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
		carry->inactive = g_optab[carry->op_code].cycles - 1;
}

/*
**	executes all of the processes, which is active
**	or decrease inactive counter (if inactive)
*/

void		execute_processes(t_session *game, t_champ *champs)
{
	t_process	*icarry;
	t_operation operations[OP_COUNT + 2]; // static?

	init_operations(operations);
	icarry = game->carrys;
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
