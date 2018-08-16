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

void	set_arg_values(int **args, int *lpc, t_session *game, bool idx_mod)
{
	int		coding_byte;
	int		i;
	int		n_of_args;

	n_of_args = 0;
	while (args[0][n_of_args] != -1) // get size of arg_types == number of arguments
		n_of_args++;

	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[*lpc + 1]);
	*lpc = move_pc(*lpc, 1);

	set_arg_types(coding_byte, args[0], n_of_args);
	i = 0;
	while (i < n_of_args) // get value for every arg_type and move pc each time
	{
		args[1][i] = get_value_by_arg(game, args[0][i], *lpc, idx_mod); // TODO: check (args[i] -> args[0][i])
		*lpc = move_pc(*lpc, get_pc_move(args[0][i]));
		i++;
	}
}

int		get_pc_move(int arg)
{
	if (arg == T_DIR)
		return (4);
	if (arg == T_IND)
		return (2);
	return (1);
}

void	set_arg_types(int coding_byte, int *args, int size) // gets bits
{
	if (size >= 1)
		args[0] = coding_byte >> 6;
	if (size >= 2)
		args[1] = ((coding_byte | 192) ^ 192) >> 4;
	if (size >= 3)
		args[2] = ((coding_byte | 240) ^ 240) >> 2;
}

int		get_value_by_arg(t_session *game, int arg, int lpc, bool idx_mod) // remove %idx for reg and dir
{
	int ind_value;
	int	value;

	if (arg == T_IND) // read value where to jump; jump to that value; read value after jump and return it
	{
		ind_value = ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]);
		if (idx_mod)
			ind_value %= IDX_MOD;
		lpc = move_pc(lpc, ind_value);
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	}
	value = 0;
	if (arg == T_REG)
		value = ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]);
	else if (arg == T_DIR)
		value = ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]);
	if (idx_mod)
		value %= IDX_MOD;
	return (value);
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
