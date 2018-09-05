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
		pc = MEM_SIZE + pc % MEM_SIZE; // pc is neg so it has to be + // TODO: pc or val (< -4096)
	return (pc);
}

/*
**	moves a pc of the carry to specified position (to right/left from the pc by val bytes)
**	sets op_code to pc internal value (op_code of the new position)
**	sets inactive counter to operation execution time (in cycles)
*/

void		update_position(t_session *game, t_carry *carry, int val)
{
	(void)game;
	(void)carry;
	carry->pc = move_pc(carry->pc, val);
}

void		update_opcode(t_session *game, t_carry *carry)
{
	carry->op_code = game->map[carry->pc];
	if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
		carry->inactive = g_optab[carry->op_code].cycles - 2;
	else
		carry->op_code = DEF_OPCODE;
}

void		print_log(t_session *game, int new_pc, int old_pc, bool is_ok) // DEL
{
	if (!is_ok)
		return ;
	printf("ADV ");
	int adv = new_pc - old_pc; // error with new_pc < old_pc
	printf("%d ", adv);
	printf("(0x%04x -> 0x%04x) ", old_pc, new_pc);
	int i = 0;
	while (i < adv)
	{
		printf("%02x ", MAP[move_pc(old_pc, i)]);
		i++;
	}
	printf("\n");
}

/*
**	executes all of the carries, which is active
**	or decrease inactive counter (if inactive)
*/

void		execute_carries(t_session *game, t_champ *champs, t_vdata *vdata, t_arg *arg)
{
	t_carry	*icarry;
	t_operation operations[OP_COUNT + 2]; // static?

	(void)vdata;
	(void)arg;
	init_operations(operations);
	icarry = game->carries;
	while (icarry)
	{
		if (icarry->op_code >= 1 && icarry->op_code <= OP_COUNT)
		{
			if (icarry->inactive == 0)
			{
				int pc_before_ex = icarry->pc; // DEL
				bool is_print = icarry->op_code != 9 || !icarry->carry; // DEL
				bool opsuc = // DEL
				operations[icarry->op_code](game, icarry, champs);
				if (opsuc && is_print) // DEL
					print_log(game, icarry->pc, pc_before_ex, true); // DEL
				icarry->op_code = DEF_OPCODE;
			}
			else
				icarry->inactive--;
		}
		else
		{
			update_opcode(game, icarry);
			if (icarry->op_code == DEF_OPCODE)
				update_position(game, icarry, 1);
		}
		icarry = icarry->next;
	}
}

/*
	t_carry	*icarry;
	t_operation operations[OP_COUNT + 2]; // static?

	init_operations(operations);
	icarry = game->carries;
	while (icarry)
	{
		// if (icarry->inactive == 0)
		// {
			if (icarry->op_code >= 1 && icarry->op_code <= OP_COUNT)
			{
				// int pc_before_ex = icarry->pc;
				// bool is_print = icarry->op_code != 9 || !icarry->carry;
				// bool opsuc =
				operations[icarry->op_code](game, icarry, champs);
				// if (opsuc && is_print)
				// 	print_log(game, icarry->pc, pc_before_ex);
				visu_drawing(vdata, game, champs, arg); // DEL
				if (game->cycle ==8910)
					usleep(1000000);
			}
			else
				update_position(game, icarry, 1);
		}
		else
			icarry->inactive--;
		icarry = icarry->next;
	}
*/