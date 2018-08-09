/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:20:33 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/09 14:20:33 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool    zjmp(t_session *game, t_carry *carry, t_champ *head)
{
	t_uint dir;

	if (CARRY == 0)
	{
		update_position(game, carry, 3);
		return (false);
	}
	dir = ft_byte_to_uint(MAP[PC + 1], MAP[PC + 2], 0, 0);
	update_position(game, carry, dir % IDX_MOD);
	return (true);
}