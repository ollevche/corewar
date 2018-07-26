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

static void		init_operations(t_operation operations[OP_COUNT + 1])
{
	operations[0] = NULL;
	// operations[1] = live;
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

void		update_position(t_process *carry, t_uint val)
{
	carry->pc += val;
	if (carry->pc > MEM_SIZE)
		carry->pc %= MEM_SIZE;
}

void			execute_processes(t_session *game, t_champ *champs)
{
	t_process	*carry;
	t_operation operations[OP_COUNT + 1];

	init_operations(operations);
	while (champs)
	{
		carry = champs->carrys;
		while (carry)
		{
			if (carry->inactive == 0)
			{
				if (carry->op_code >= 1 && carry->op_code <= 16)
					operations[carry->op_code](game, champs, carry);
				else
					update_position(carry);
			}
			else
				carry->inactive--;
			carry = carry->next;
		}
		champs = champs->next;
	}
}
