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
	//	TODO: this
	return (false);
}

bool		read_champ(t_champ **champs, char *filename)
{
	int		fd;
	bool	is_champ;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		return (false);
	}
	is_champ = reading(champs, fd, filename);
	close(fd);
	return (is_champ);
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
			if (!read_champ(&champs, args[i]))
			{
				free_champs(&champs);
				terminate();
			}
		i++;
	}
	return (champs);
}
