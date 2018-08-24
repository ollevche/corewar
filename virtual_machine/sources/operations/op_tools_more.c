/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 13:32:28 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/24 13:32:29 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

/*
** T_REG(1) = 1, 3, 5, 7
** T_DIR(2) = 2, 3, 6, 7
** T_IND(4) = 4, 5, 6, 7
*/

bool	check_cbyte(int args[2][4], int op_code, int size) // TODO: refact
{
    int i;

    i = 0;
    while (i < size)
    {
        if (args[0][i] == REG_CODE)
            if (OP_ATYP(op_code, i) != 1 || OP_ATYP(op_code, i) != 3
            || OP_ATYP(op_code, i) != 5 || OP_ATYP(op_code, i) != 7)
                return (false);
        if (args[0][i] == DIR_CODE)
            if (OP_ATYP(op_code, i) != 2 || OP_ATYP(op_code, i) != 3
            || OP_ATYP(op_code, i) != 6 || OP_ATYP(op_code, i) != 7)
                return (false);
        if (args[0][i] == IND_CODE)
            if (OP_ATYP(op_code, i) != 1 || OP_ATYP(op_code, i) != 5
            || OP_ATYP(op_code, i) != 6 || OP_ATYP(op_code, i) != 7)
                return (false);
        i++;
    }
	return (true);

}

bool	check_reg(int *value, t_session *game, t_carry *carry, int jmp)
{
	if (IS_REG(*value))
	{
		*value = REGS[*value - 1];
		return (true);
	}
	update_position(game, carry, jmp + 1);
	return (false);
}

void    write_to_map(t_session *game, int pos, int value)
{
	MAP[pos] = (value & -16777216) >> 24;
	MAPVAL(pos, 1) = (value & 16711680) >> 16;
	MAPVAL(pos, 2) = (value & 65280) >> 8;
	MAPVAL(pos, 3) = value & 255;
}
