/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:24:49 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/18 14:24:49 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

static bool	set_flag(char **args, int *i)
{
	(void)args;
	(void)i;	
	return (false);
}

static void	terminate_input(t_champ *champs)
{
	// free_champs(champs);
	if (errno)
		perror("Default error: ");
	exit(EXIT_FAILURE);
}

t_champ		*read_input(int argc, char **args)
{
	t_champ	*champs;
	int		i;

	champs = NULL;
	i = 1;
	while (i < argc)
	{
		if (!set_flag(args, &i))
			if (!read_champ(champs, args[i]))
				terminate_input(champs);
		i++;
	}
	return (champs);
}
