/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:15:22 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/09 15:15:23 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	ld(t_session *game, t_carry *carry, t_champ *head)
{
	t_uint	coding_byte;
	t_uint		reg;
	t_uint 	value;
	int 	args[2];
	int		lpc;

	(void) head;
	lpc = PC;
	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]);
	lpc = move_pc(game, lpc, 1);
	get_arg_types(coding_byte, &args[0], &args[1], NULL);
	value = get_value_by_arg(carry, game, args[0], lpc);
	lpc = (args[0] == T_DIR ? move_pc(game, lpc, 4) : move_pc(game, lpc, 2));
	reg = get_value_by_arg(carry, game, args[1], lpc);
	lpc = move_pc(game, lpc, 1);
	if (IS_REG(reg))
		REGS[reg - 1] = value;
	update_position(game, carry, lpc + 1);
	return (IS_REG(reg));
	// char *binary = ft_uitobase(coding_byte, 2);
	// ft_printf("\t\t\t%u\n| %s |\n %b %b\n", coding_byte, binary, arg1, arg2);
}