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

#define OPTAB g_optab[op_code]

int			set_arg_types(int coding_byte, int *args, int size)
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

int			get_pc_move(int arg, int label_size)
{
	if (arg == DIR_CODE)
		return (2 + 2 * (1 - label_size));
	if (arg == IND_CODE)
		return (2);
	return (1);
}

/*
** original vm is broken (reads 2 bytes instead of 4) at lld
** line 61
*/

static int	get_ind(t_session *game, int lpc, int pc, int op_code)
{
	short ind_value;

	ind_value = read_int(game, lpc, 2, true);
	if (OPTAB.ind_idx)
		ind_value %= IDX_MOD;
	if (op_code == 3)
		return (ind_value);
	lpc = move_pc(pc, ind_value);
	if (op_code == 13)
		return (read_int(game, lpc, 2, false));
	return (read_int(game, lpc, 4, false));
}

bool		set_arg_values(int args[2][4], int *lpc, t_session *game,
																int op_code)
{
	int		coding_byte;
	int		i;
	int		n_args;
	int		valid_args;
	int		pc;

	n_args = OPTAB.nb_params;
	pc = *lpc;
	coding_byte = read_int(game, *lpc, 1, true);
	*lpc = move_pc(*lpc, 1);
	if (!(valid_args = set_arg_types(coding_byte, args[0], n_args)))
		return (false);
	i = -1;
	while (i + 1 < n_args)
	{
		i++;
		if (args[0][i] == IND_CODE)
			args[1][i] = get_ind(game, *lpc, pc, op_code);
		else if (args[0][i] == REG_CODE || args[0][i] == DIR_CODE)
			args[1][i] = get_value_by_arg(game, args[0][i], *lpc, op_code);
		else
			continue ;
		*lpc = move_pc(*lpc, get_pc_move(args[0][i], OPTAB.label_size));
	}
	return (n_args == valid_args && check_cbyte(args, op_code, n_args));
}

int			get_value_by_arg(t_session *game, int arg, int lpc, int op_code)
{
	if (arg == REG_CODE)
		return (read_int(game, lpc, 1, true));
	if (arg == DIR_CODE)
	{
		if (g_optab[op_code].label_size == 1)
			return (read_int(game, lpc, 2, true));
		else
			return (read_int(game, lpc, 4, true));
	}
	return (0);
}
