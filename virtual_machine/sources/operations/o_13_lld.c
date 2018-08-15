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
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (2 + 1)), false);
	arg_types[2] = -1;
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, false)))
	{
		update_position(game, carry, lpc + 1);
		return (false);
	}
	if (IS_REG(VAL2))
		REGS[VAL2 - 1] = VAL1;
	update_position(game, carry, lpc + 1);
	return (IS_REG(VAL2));
}