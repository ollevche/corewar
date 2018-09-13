/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:37:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/22 19:37:25 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void	free_session(t_session **game)
{
	t_carry *carries;

	if (!game || !*game)
		return ;
	carries = (*game)->carries;
	free_carries(&carries);
	free(*game);
	*game = NULL;
}

void	free_champs(t_champ **champs)
{
	t_champ *trash;
	t_champ *iter;

	if (!champs || !*champs)
		return ;
	iter = *champs;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free(trash->name);
		free(trash->comment);
		free(trash->code);
		free(trash);
	}
	*champs = NULL;
}

void	free_carries(t_carry **carries)
{
	t_carry *trash;
	t_carry *iter;

	if (!carries || !*carries)
		return ;
	iter = *carries;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free(trash);
	}
	*carries = NULL;
}
