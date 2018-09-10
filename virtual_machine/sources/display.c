/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:41:22 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/10 17:41:23 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void	display_contestants(t_champ *champs)
{
	ft_printf("Introducing contestants...\n");
	while (champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		champs->id, champs->code_len, champs->name, champs->comment);
		champs = champs->next;
	}
}

void    display_winner(t_champ *winner)
{
	ft_printf("Contestant %d, \"%s\", has won !\n", winner->id, winner->name);
}

void    display_usage()
{
	ft_printf("TODO: usage text\n");
	terminate(NULL);
}
