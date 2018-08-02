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

static bool	set_flag(char **args, int *i, int *dump) // TODO: rewrite
{
	if (!ft_strcmp("-dump", args[*i]))
	{
		(*i)++;
		*dump = ft_atoi(args[*i]);
		return (true);
	}
	else if (!ft_strcmp("-n", args[*i]))
	{
		(*i)++;
		//TODO: -n flag [champs ids should be set here]
		return (true);
	}
	return (false);
}

static bool	read_champ(t_champ **champs, char *filename)
{
	int		fd;
	bool	is_champ;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		errno = 0;
		return (false);
	}
	is_champ = reading(champs, fd, filename);
	close(fd);
	return (is_champ);
}

t_champ		*read_input(int argc, char **args, int *dump)
{
	t_champ	*champs;
	int		i;

	champs = NULL;
	*dump = -1;
	i = 1;
	while (i < argc)
	{
		if (!set_flag(args, &i, dump))
			if (!read_champ(&champs, args[i]))
			{
				free_champs(&champs);
				terminate();
			}
		i++;
	}
	return (champs);
}
