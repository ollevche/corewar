/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_06_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	or(t_session *game, t_carry *carry, t_champ *head)
{
	int		arg_types[3];
	int		arg_values[3];
	int		coding_byte;
	int		lpc;

	lpc = PC;
	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]);
	lpc = move_pc(game, lpc, 1);
	get_arg_types(coding_byte, arg_types[0], arg_types[1], arg_types[2]);
	arg_values[0] = get_value_by_arg(game, arg_types[0], lpc, false);
	lpc = move_pc(game, lpc, get_pc_move(arg_values[0]));
	arg_values[1] = get_value_by_arg(game, arg_types[1], lpc, false);
	lpc = move_pc(game, lpc, get_pc_move(arg_values[1]));
	arg_values[2] = get_value_by_arg(game, arg_types[2], lpc, false);
	lpc = move_pc(game, lpc, get_pc_move(arg_values[2]));
	if (IS_REG(arg_values[2]))
	{
		REGS[arg_values[2] - 1] = arg_values[0] | arg_values[1];
		CARRY = (REGS[arg_values[2] - 1] == 0 ? true : false);
	}
	update_position(game, carry, lpc + 1);
	return (IS_REG(arg_values[2]));
}
