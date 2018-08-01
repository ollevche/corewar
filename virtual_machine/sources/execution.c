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

static void	init_operations(t_operation operations[OP_COUNT + 1])
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
}

void		update_position(t_session *game, t_process *carry, int val)
{
	carry->pc += val;
	if (carry->pc >= MEM_SIZE)
		carry->pc %= MEM_SIZE;
	else if (carry->pc < 0)
		carry->pc = MEM_SIZE + carry->pc; // carry->pc is neg so it has to be +
	carry->op_code = game->map[carry->pc];
	if (carry->op_code == 1) // DEL
		carry->inactive += 10; // TODO: struct from op.c with op-s info
}

void		execute_processes(t_session *game, t_champ *champs)
{
	t_process	*carry;
	t_champ		*a_champ;
	t_operation operations[OP_COUNT + 1];

	init_operations(operations);
	a_champ = champs;
	while (a_champ)
	{
		carry = a_champ->carrys;
		while (carry)
		{
			if (carry->inactive == 0)
			{
				if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
					operations[carry->op_code](game, a_champ, carry, champs);
				else
					update_position(game, carry, 1);
			}
			else
				carry->inactive--;
			carry = carry->next;
		}
		a_champ = a_champ->next;
	}
}
