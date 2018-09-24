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

#define BTI ft_byte_to_uint
#define MVAL1 MAPVAL(lpc, n)
#define MVAL2 MAPVAL(lpc, n + 1)
#define MVAL3 MAPVAL(lpc, n + 2)
#define MVAL4 MAPVAL(lpc, n + 3)

/*
** T_REG(1) = 1, 3, 5, 7
** T_DIR(2) = 2, 3, 6, 7
** T_IND(4) = 4, 5, 6, 7
*/

bool			check_cbyte(int args[2][4], int op_code, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (args[0][i] == REG_CODE)
			if (!(OP_ATYP(op_code, i) & T_REG))
				return (false);
		if (args[0][i] == DIR_CODE)
			if (!(OP_ATYP(op_code, i) & T_DIR))
				return (false);
		if (args[0][i] == IND_CODE)
			if (!(OP_ATYP(op_code, i) & T_IND))
				return (false);
		i++;
	}
	return (true);
}

bool			check_reg(int *value, t_carry *carry, int jmp)
{
	if (IS_REG(*value))
	{
		*value = REGS[*value - 1];
		return (true);
	}
	update_position(carry, jmp + 1);
	return (false);
}

void			write_to_map(t_session *game, int pos, int value, int champ_id)
{
	MAPVAL(pos, 0) = (value & -16777216) >> 24;
	MAPVAL(pos, 1) = (value & 16711680) >> 16;
	MAPVAL(pos, 2) = (value & 65280) >> 8;
	MAPVAL(pos, 3) = value & 255;
	game->spot_map[move_pc(pos, 0)] = champ_id;
	game->spot_map[move_pc(pos, 1)] = champ_id;
	game->spot_map[move_pc(pos, 2)] = champ_id;
	game->spot_map[move_pc(pos, 3)] = champ_id;
}

unsigned int	read_int(t_session *game, int lpc, int n_bytes, bool plus_one)
{
	int	n;

	n = 0;
	if (plus_one)
		n = 1;
	if (n_bytes == 1)
		return (BTI(0, 0, 0, MVAL1));
	if (n_bytes == 2)
		return ((short)BTI(0, 0, MVAL1, MVAL2));
	if (n_bytes == 4)
		return (BTI(MVAL1, MVAL2, MVAL3, MVAL4));
	return (0);
}
