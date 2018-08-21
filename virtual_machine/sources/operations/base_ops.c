/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 13:05:29 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/16 13:05:29 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"
// TODO: base func for add/sub/etc
static void	copy_carry(t_carry *to, t_carry *from)
{
	int	i;

	i = -1;
	while (++i < 16)
		to->regs[i] = from->regs[i];
	to->pc = from->pc;
	to->carry = from->carry;
	to->last_live = from->last_live;
}

bool		base_fork(t_session *game, t_carry *carry, bool idx)
{
	short	pos;
	t_carry	*fork;

	pos = get_value_by_arg(game, T_DIR, carry->pc, 1);
	// ft_printf("\t\t\t\tpos = %x\n", pos); // DEL
	if (idx)
		pos %= IDX_MOD;
	fork = new_carry(&game->carrys, carry->regs[0]);
	RET_CHECK(fork, false);
	copy_carry(fork, carry);
	update_position(game, fork, pos);
	update_position(game, carry, 3);
	game->carry_num++;
	// fork->inactive++; // TODO: check if the fork runs in current cycle
	return (true);
}
