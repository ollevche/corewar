/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:19:17 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/14 15:19:17 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	free_ret(int *arg_types, int *arg_values, bool ret)
{
	if (arg_types)
		free(arg_types);
	if (arg_values)
		free(arg_values);
	return (ret);
}

bool	ldi(t_session *game, t_carry *carry, t_champ *head)
{
	int 	*arg_values;
	int 	*arg_types;
	int		lpc;
	int		p;

	lpc = PC;
	RET_CHECK(arg_types = (int*)ft_memalloc(sizeof(int) * (3 + 1)), false);
	arg_types[3] = -1;
	if (!(arg_values = get_arg_values(arg_types, &lpc, game, true)))
	{
		update_position(game, carry, lpc + 1);
		return (free_ret(arg_types, NULL, false));
	}
	if (IS_REG(AVAL3))
	{
		FREE_RET(!(ATYP1 == T_REG && !check_reg(&AVAL1, game, carry, lpc)));
		FREE_RET(!(ATYP2 == T_REG && !check_reg(&AVAL2, game, carry, lpc)));
		p = ((AVAL1 + AVAL2) % IDX_MOD) + PC;
		REGS[AVAL3] = ft_byte_to_uint(MAP[p + 1], MAP[p + 2], MAP[p + 3], MAP[p + 4]);
		CARRY = (REGS[AVAL3 - 1] == 0 ? true : false);
	}
	update_position(game, carry, lpc + 1);
	return (free_ret(arg_types, arg_values, true));
}
