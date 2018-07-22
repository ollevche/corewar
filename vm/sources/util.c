/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:54:55 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/22 17:54:55 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ *new_champ(t_champ **champs)
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

void	free_champs(t_champ **champs)
{
	(void)champs;
	//	TODO: this
}
