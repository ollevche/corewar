/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_12-13_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:11:42 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/15 15:11:42 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

static void	copy_carry(t_carry *to, t_carry *from)
{
	int i;

	i = -1;
	while (++i < 16)
		to->regs[i] = from->regs[i];
	to->pc = from->pc;
	to->carry = from->carry;
	to->last_live = from->last_live;
}

static bool	base_fork(t_session *game, t_carry *carry, t_champ *head, bool idx)
{
	int     pos;
	t_carry *fork;

	pos = get_value_by_arg(game, T_DIR, carry->pc, idx);
	fork = new_carry(&game->carrys, carry->regs[0]);
	RET_CHECK(fork, false);
	copy_carry(fork, carry);
	update_position(game, fork, pos);
	// fork->inactive++; // TODO: check if the fork runs in current cycle
	return (true);
}

bool		op_fork(t_session *game, t_carry *carry, t_champ *head)
{
	return (base_fork(game, carry, head, true));
}

bool		op_lfork(t_session *game, t_carry *carry, t_champ *head)
{
	return (base_fork(game, carry, head, false));
}
