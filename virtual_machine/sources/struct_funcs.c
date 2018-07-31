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

void	del_process(t_process **carrys, t_process *target) // TODO: test it
{
	t_process	*iter;

	iter = *carrys;
	if (!iter)
		return ;
	if (iter == target)
		*carrys = iter->next;
	else
	{
		while (iter->next != target)
			iter = iter->next;
		iter->next = target->next;
	}
	target->next = NULL;
	free_processes(target);
}

t_champ	*get_champ_by_id(t_champ *head, t_uint id)
{
	while (head && head->id != id)
		head = head->next;
	return (head);
}
