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
	RET_CHECK(champ, NULL);
	champ->carrys = NULL;
	champ->name = NULL;
	champ->comment = NULL;
	champ->code_len = 0;
	champ->code = NULL;
	champ->id = 0;
	champ->next = NULL;
	if (*champs)
	{
		iter = *champs;
		while (iter->next)
			iter = iter->next;
		iter->next = champ;
	}
	else
		*champs = champ;
	return (champ);
}

bool	new_carry(t_process **all_carrys, t_uint first_reg)
{
	t_process	*iter;
	t_process	*carry;

	carry = (t_process*)malloc(sizeof(t_process));
	RET_CHECK(carry, false);
	carry->regs[0] = first_reg;
	ft_memset(carry->regs + 1, 0, REG_NUMBER);
	carry->pc = 0;
	carry->carry = false;
	carry->inactive = 0;
	carry->op_code = 0;
	carry->last_live = 0;
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
