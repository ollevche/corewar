/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_04_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:41:31 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/08 13:41:32 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool	add(t_session *game, t_carry *carry, t_champ *head)
{
	int r1;
	int r2;
	int r3;

	(void)head;
	r1 = (int)ft_byte_to_uint(0, 0, 0, MAP[PC + 2]);
	r2 = (int)ft_byte_to_uint(0, 0, 0, MAP[PC + 3]);
	r3 = (int)ft_byte_to_uint(0, 0, 0, MAP[PC + 4]);
	if (!IS_REG(r1) || !IS_REG(r2) || !IS_REG(r3))
	{
		update_position(game, carry, 5);
		return (false);
	}
	REGS[r3] = REGS[r1] + REGS[r2];
	carry->carry = (REGS[r3] == 0 ? true : false);
	update_position(game, carry, 5);
	return (true);
}