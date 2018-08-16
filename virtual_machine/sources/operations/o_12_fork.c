/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 13:06:22 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/16 13:06:22 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

bool		op_fork(t_session *game, t_carry *carry, t_champ *head)
{
	(void)head;
	return (base_fork(game, carry, true));
}
