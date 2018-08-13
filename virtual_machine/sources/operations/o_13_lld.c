/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:51:26 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/26 13:51:27 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	lld(t_session *game, t_carry *carry, t_champ *head)
{
	int		coding_byte;
	int		reg;
	int 	value;
	int 	args[2];
	int		lpc;

	(void) head;
	lpc = PC;
	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]);
	lpc = move_pc(game, lpc, 1);
	get_arg_types(coding_byte, &args[0], &args[1], NULL);
	value = get_value_by_arg(game, args[1], lpc, false);
	lpc = move_pc(game, lpc, get_pc_move(args[0]));
	reg = get_value_by_arg(game, args[1], lpc, false);
	lpc = move_pc(game, lpc, 1);
	if (IS_REG(reg))
		REGS[reg - 1] = value;
	update_position(game, carry, lpc + 1);
	return (IS_REG(reg));
}
