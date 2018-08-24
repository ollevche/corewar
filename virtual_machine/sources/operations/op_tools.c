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

static int	get_pc_move(int arg, int label_size)
{
	if (arg == DIR_CODE)
		return (2 + 2 * (1 - label_size));
	if (arg == IND_CODE)
		return (2);
	return (1);
}

static int	get_idx_ind(t_session *game, int lpc, int op_code)
{
	short ind_value;

	ind_value = ft_byte_to_uint(0, 0, MAPVAL(lpc, 1), MAPVAL(lpc, 2));
	ind_value %= IDX_MOD;
	if (op_code == 3 || op_code == 11) // st or sti
		return (ind_value);
	lpc = move_pc(lpc, ind_value);
	return (ft_byte_to_uint(MAPVAL(lpc, 1), MAPVAL(lpc, 2), MAPVAL(lpc, 3), MAPVAL(lpc, 4)));
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

	coding_byte = ft_byte_to_uint(0, 0, 0, MAPVAL(*lpc, 1));
	*lpc = move_pc(*lpc, 1);
	if (!(valid_args = set_arg_types(coding_byte, args[0], n_of_args)))
		return (false);

	i = -1; // TODO: this is ugly piece of code, but correct one (refactor this) // TODO: this isn't correct; (2 helltrains test)
	while (i + 1 < n_of_args) // get value for every arg_type and move pc each time
	{
		i++;
		if (args[0][i] == IND_CODE && g_optab[op_code].ind_idx)
			args[1][i] = get_idx_ind(game, *lpc, op_code);
		else if (args[0][i] == REG_CODE || args[0][i] == DIR_CODE)
			args[1][i] = get_value_by_arg(game, args[0][i], *lpc, op_code);
		else
			continue ;
		*lpc = move_pc(*lpc, get_pc_move(args[0][i], g_optab[op_code].label_size));
	}
	return (n_of_args == valid_args);
}

int		get_value_by_arg(t_session *game, int arg, int lpc, int op_code)
{
	int ind_value;

	if (arg == IND_CODE) // read value where to jump; jump to that value; read value after jump and return it
	{
		ind_value = ft_byte_to_uint(0, 0, MAPVAL(lpc, 1), MAPVAL(lpc, 2));
		if (op_code == 3 || op_code == 11) // st or sti
			return (ind_value);
		lpc = move_pc(lpc, ind_value); // TODO: st and sti writes to the map by pointer (IND)
		return (ft_byte_to_uint(MAPVAL(lpc, 1), MAPVAL(lpc, 2), MAPVAL(lpc, 3), MAPVAL(lpc, 4)));
	}
	if (arg == REG_CODE)
		return (ft_byte_to_uint(0, 0, 0, MAPVAL(lpc, 1)));
	if (arg == DIR_CODE)
	{
		if (g_optab[op_code].label_size == 1)
			return (ft_byte_to_uint(0, 0, MAPVAL(lpc, 1), MAPVAL(lpc, 2)));
		else
			return (ft_byte_to_uint(MAPVAL(lpc, 1), MAPVAL(lpc, 2), MAPVAL(lpc, 3), MAPVAL(lpc, 4)));
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
