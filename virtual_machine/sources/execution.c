/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:17:39 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/26 13:17:39 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void		execute_processes(t_session *game, t_champ *champs)
{
	t_process	*carry_iter;

	while (champs)
	{
		carry_iter = champs->carrys;
		while (carry_iter)
		{
			if (carry_iter->inactive == 0)
			{
				if (carry_iter->op_code >= 1 && carry_iter->op_code <= 16)
				{
					// array function call // func_arr[carry_iter->op_code](args);
				}
				else
					update_position(carry_iter);
			}
			else
				carry_iter->inactive--;
			carry_iter = carry_iter->next;
		}
		champs = champs->next;
	}
}
