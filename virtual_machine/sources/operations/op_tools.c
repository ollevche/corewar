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

int		*get_arg_values(int *arg_types, int *lpc, t_session *game, bool idx_mod)
{
	int		coding_byte;
	int		*arg_values;
	int		i;
	int		n_of_args;

	n_of_args = 0;
	while (arg_types[n_of_args] != -1) // get size of arg_types == number of arguments
		n_of_args++;

	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[*lpc + 1]);
	*lpc = move_pc(game, *lpc, 1);

	get_arg_types(coding_byte, arg_types[0], arg_types[1], arg_types[2]);
	RET_CHECK(arg_values = (int*)ft_memalloc(sizeof(int) * n_of_args), NULL)
	i = 0;
	while (i < n_of_args) // get value for every arg_type and move pc each time
	{
		arg_values[i] = get_value_by_arg(game, arg_types[i], *lpc, idx_mod);
		*lpc = move_pc(game, *lpc, get_pc_move(arg_values[i]));
		i++;
	}
	return (arg_values);
}

int		get_pc_move(int arg)
{
	if (arg == T_DIR)
		return (4);
	if (arg == T_IND)
		return (2);
	return (1);
}

void	get_arg_types(int coding_byte, int *arg1, int *arg2, int *arg3)
{
	if (arg1 != NULL)
		*arg1 = coding_byte >> 6;
	if (arg2 != NULL)
		*arg2 = ((coding_byte | 192) ^ 192) >> 4;
	if (arg3 != NULL)
		*arg3 = ((coding_byte | 240) ^ 240) >> 2;
}

int		get_value_by_arg(t_session *game, int arg, int lpc, bool idx_mod)
{
	int ind_value;

	if (arg == T_REG)
		return (ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]));
	if (arg == T_DIR)
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	if (arg == T_IND) // read value where to jump; jump to that value; read value after jump and return it
	{
		ind_value = ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]);
		if (idx_mod)
			ind_value %= IDX_MOD;
		lpc = move_pc(game, lpc, ind_value);
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	}
	return (0);
}

bool	check_reg(int *value, t_session *game, t_carry *carry, int lpc)
{
	if (IS_REG(*value))
	{
		*value = REGS[*value - 1];
		return (true);
	}
	update_position(game, carry, lpc + 1);
	return (false);
}
