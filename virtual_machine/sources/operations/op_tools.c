/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 17:00:25 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/09 17:00:26 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void	get_arg_types(int coding_byte, int *arg1, int *arg2, int *arg3)
{
	*arg1 = coding_byte >> 6;
	*arg2 = ((coding_byte | 192) ^ 192) >> 4;
	if (arg3 != NULL)
		*arg3 = ((coding_byte | 240) ^ 240) >> 2;
}

t_uint	get_value_by_arg(t_carry *carry, t_session *game, int arg, int lpc)
{
	t_uint ind_value;

	if (arg == T_REG)
		return (ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]));
	if (arg == T_DIR)
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	if (arg == T_IND) // read value where to jump; jump to that value; read value after jump and return it
	{
		ind_value = ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]);
		ind_value %= IDX_MOD;
		lpc = move_pc(game, lpc, ind_value);
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	}
	return (0);
}