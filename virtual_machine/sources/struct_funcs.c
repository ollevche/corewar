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

/*
**	norminette wont see REG_NUMBER, hence RN
*/

#define RN REG_NUMBER

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
	champ->period_lives = 0;
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

t_carry	*new_carry(t_carry **all_carries, int first_reg)
{
	t_carry	*carry;

	carry = (t_carry*)malloc(sizeof(t_carry));
	RET_CHECK(carry, NULL);
	ft_memset(carry->regs, 0, RN * sizeof(int));
	carry->regs[0] = (t_uint)first_reg;
	carry->pc = 0;
	carry->carry = false;
	carry->inactive = 0;
	carry->op_code = 0;
	carry->last_live = -1;
	carry->champ = first_reg;
	carry->next = *all_carries;
	*all_carries = carry;
	return (carry);
}

void	del_carry(t_carry **head, t_carry *prev, t_carry *target)
{
	if (*head == target)
		*head = target->next;
	else
		prev->next = target->next;
	target->next = NULL;
	free_carries(&target);
}

t_champ	*get_champ_by_id(t_champ *head, int id)
{
	while (head && head->id != id)
		head = head->next;
	return (head);
}

t_champ	*get_last_champ(t_champ *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
