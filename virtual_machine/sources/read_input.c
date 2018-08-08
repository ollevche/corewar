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

static bool		set_flag(char **args, int *i, t_arg arg)
{
	(void)args;
	(void)i;
	(void)arg;
	return (false);
}

static t_champ	*read_file(t_champ **champs, char *filename)
{
	int		fd;
	t_champ	*champ;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		errno = 0;
		return (false);
	}
	champ = read_champ(champs, fd, filename);
	close(fd);
	return (champ);
}

t_champ			*read_input(int argc, char **args, t_arg arg)
{
	t_champ	*champs;
	t_champ	*ichamp;
	int		i;

	champs = NULL;
	i = 1;
	while (i < argc)
	{
		if (!set_flag(args, &i, arg))
			if ((ichamp = read_file(&champs, args[i])))
				ichamp->id = --arg.champ_id;
		if (!ichamp)
		{
			free_champs(&champs);
			terminate();
		}
		i++;
	}
	return (champs);
}
