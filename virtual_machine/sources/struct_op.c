/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:37:16 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/22 19:37:16 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ	*new_champ(t_champ **champs)
{
	t_champ *champ;
	t_champ *iter;

	champ = (t_champ*)malloc(sizeof(t_champ));
	if (*champs)
	{
		iter = *champs;
		while (iter->next)
			iter = iter->next;
		iter->next = champ;
	}
	else
		*champs = champ;
	champ->alive = true;
	champ->carrys = NULL;
	champ->code = NULL;
	champ->comment = NULL;
	champ->name = NULL;
	champ->next = NULL;
	return (champ);
}

bool	new_carry(t_process **all_carrys, uint first_reg)
{
	t_process	*iter;
	t_process	*carry;
	uint		i;

	carry = (t_process*)malloc(sizeof(t_process));
	RET_CHECK(carry, false);
	carry->regs[0] = first_reg;
	i = 1;
	while (i < REG_SIZE)
		carry->regs[i++] = 0;
	carry->pc = 0;
	carry->carry = false;
	carry->inactive = 0;
	carry->next = NULL;
	if (*all_carrys)
	{
		iter = *all_carrys;
		while (iter->next)
			iter = iter->next;
		iter->next = carry;
	}
	else
		*all_carrys = carry;
	return (true);
}
