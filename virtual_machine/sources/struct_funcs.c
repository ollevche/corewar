/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:37:16 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/22 19:37:16 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

t_champ	*new_champ(t_champ **champs)
{
	t_champ *champ;
	t_champ *iter;

	champ = (t_champ*)malloc(sizeof(t_champ));
	RET_CHECK(champ, NULL);
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

t_carry	*new_carry(t_carry **all_carrys, int first_reg)
{
	t_carry	*carry;

	carry = (t_carry*)malloc(sizeof(t_carry));
	RET_CHECK(carry, NULL);
	carry->regs[0] = first_reg; // t_uint = int
	ft_memset(carry->regs + 1, 0, REG_NUMBER - 1);
	carry->pc = 0;
	carry->carry = false;
	carry->inactive = 0;
	carry->op_code = 0;
	carry->last_live = -1;
	carry->next = *all_carrys;
	*all_carrys = carry;
	return (carry);
}

void	del_carry(t_carry **head, t_carry **prev, t_carry *target)
{
	if (*prev == NULL)
	{
		*head = (*head)->next;
		*prev = *head;
	}
	else
		(*prev)->next = target->next;
	target->next = NULL;
	free_carries(target);
}

t_champ		*get_champ_by_id(t_champ *head, int id)
{
	while (head && head->id != id)
		head = head->next;
	return (head);
}
