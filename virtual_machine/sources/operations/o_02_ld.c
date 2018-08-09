/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:15:22 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/09 15:15:23 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void	get_arg_types(int coding_byte, int *arg1, int *arg2, int *arg3)
{
	
}

bool	ld(t_session *game, t_carry *carry, t_champ *head)
{
	t_uint	coding_byte;

	(void) head;
	coding_byte = ft_byte_to_uint(0, 0, 0, PC[MAP + 1]);
	char *binary = ft_uitobase(coding_byte, 2);
	printf("%u | %s |\n", coding_byte, binary);
		return true;
}