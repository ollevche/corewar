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

static int	set_arg_types(int coding_byte, int *args, int size) // gets bits
{
	int i;
	int valid;

	if (size >= 1)
		args[0] = coding_byte >> 6;
	if (size >= 2)
		args[1] = ((coding_byte | 192) ^ 192) >> 4;
	if (size >= 3)
		args[2] = ((coding_byte | 240) ^ 240) >> 2;
	i = -1;
	valid = 0;
	while (++i < size)
		if (args[i] >= 1 && args[i] <= 3)
			valid++;
	return (valid);
}

bool	set_arg_values(int args[2][4], int *lpc, t_session *game, int op_code)
{
	int		coding_byte;
	int		i;
	int		n_of_args;
	int		valid_args;

	n_of_args = 0;
	while (args[0][n_of_args] != -1) // get size of arg_types == number of arguments
		n_of_args++;

	coding_byte = ft_byte_to_uint(0, 0, 0, MAP[*lpc + 1]);
	*lpc = move_pc(*lpc, 1);
	if (!(valid_args = set_arg_types(coding_byte, args[0], n_of_args)))
		return (false);

	i = 0;
	while (i < n_of_args) // get value for every arg_type and move pc each time
	{
		if (args[0][i] == IND_CODE && g_optab[op_code].ind_idx)
			args[1][i] = get_idx_ind(game, *lpc);
		else if (args[0][i] == REG_CODE || args[0][i] == DIR_CODE)
		{
			args[1][i] = get_value_by_arg(game, args[0][i], *lpc, g_optab[op_code].label_size);
			*lpc = move_pc(*lpc, get_pc_move(args[0][i], g_optab[op_code].label_size));
		}
		i++;
	}
	return (n_of_args == valid_args);
}

int		get_pc_move(int arg, int label_size)
{
	if (arg == DIR_CODE)
		return (2 + 2 * (1 - label_size));
	if (arg == IND_CODE)
		return (2);
	return (1);
}

int		get_idx_ind(t_session *game, int lpc)
{
	int ind_value;

	ind_value = ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]);
	ind_value %= IDX_MOD;
	lpc = move_pc(lpc, ind_value);
	return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
}

int		get_value_by_arg(t_session *game, int arg, int lpc, int label_size)
{
	int ind_value;

	if (arg == IND_CODE) // read value where to jump; jump to that value; read value after jump and return it
	{
		ind_value = ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]);
		lpc = move_pc(lpc, ind_value); // TODO: st and sti writes to the map by pointer (IND)
		return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	}
	if (arg == REG_CODE)
		return (ft_byte_to_uint(0, 0, 0, MAP[lpc + 1]));
	if (arg == DIR_CODE)
	{
		if (label_size == 1)
			return (ft_byte_to_uint(0, 0, MAP[lpc + 1], MAP[lpc + 2]));
		else
			return (ft_byte_to_uint(MAP[lpc + 1], MAP[lpc + 2], MAP[lpc + 3], MAP[lpc + 4]));
	}
	return (0);
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
