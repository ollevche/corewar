/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 12:14:38 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/11 12:14:38 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

int			move_pc(int pc, int val)
{
	pc += val;
	if (pc >= MEM_SIZE)
		pc %= MEM_SIZE;
	else if (pc < 0)
		pc = MEM_SIZE + pc % MEM_SIZE;
	return (pc);
}

/*
**  moves a pc of the carry to specified position ▽
**  (to right/left from the pc by val bytes)
*/

void		update_position(t_carry *carry, int val)
{
	carry->pc = move_pc(carry->pc, val);
}

/*
**	sets op_code to pc internal value (op_code of the new position) ▽
**	sets inactive counter to operation execution time (in cycles)
*/

void		update_opcode(t_session *game, t_carry *carry)
{
	carry->op_code = game->map[carry->pc];
	if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
		carry->inactive = g_optab[carry->op_code].cycles - 2;
	else
		carry->op_code = DEF_OPCODE;
}

int			count_champs(t_champ *champs)
{
	int champs_count;

	champs_count = 0;
	while (champs)
	{
		champs_count++;
		champs = champs->next;
	}
	return (champs_count);
}
