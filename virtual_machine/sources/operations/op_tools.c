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
		*arg3 = ((coding_byte | 240) ^ 240) >> 2; //comment
}

int		get_value_by_arg(t_carry *carry, t_session *game, int arg)
{
	(void)carry;
	(void)game;
	(void)arg;
	if (arg == 0)
	return (0);
}