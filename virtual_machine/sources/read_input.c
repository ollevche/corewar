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

#define NOT_FLAG 0
#define INVALID_FLAG -1
#define VALID_FLAG 1

/*
**	what: true - dump; false - n
*/

static int		set_numerical(char **args, int *i, t_arg *arg, bool what)
{
	if (what)
		arg->dump = ft_atoi(args[++(*i)]);
	else
		arg->champ_id = ft_atoi(args[++(*i)]);
	if (!ft_isnumber(args[*i]))
	{
		ft_printf("Flag %s has invalid number\n", what ? "-dump" : "-n");
		return (INVALID_FLAG);
	}
	return (VALID_FLAG);
}

static int		set_flag(char **args, int *i, t_arg *arg, t_champ *head)
{
	if (!ft_strcmp(args[*i], "-dump"))
		return (set_numerical(args, i, arg, true));
	else if (!ft_strcmp(args[*i], "-n"))
	{
		if (set_numerical(args, i, arg, false) == VALID_FLAG)
			if (!get_champ_by_id(head, arg->champ_id))
				return (VALID_FLAG);
		ft_printf("Id '%d' is already taken by another champ\n", arg->champ_id);
		return (INVALID_FLAG);
	}
	else if (!ft_strcmp(args[*i], "-v"))
		arg->is_visual = true;
	else if (!ft_strcmp(args[*i], "-log"))
		arg->log = true;
	else
		return (NOT_FLAG);
	return (VALID_FLAG);
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

static int		get_next_id(t_champ *champs, t_arg *arg)
{
	while (get_champ_by_id(champs, arg->champ_id))
		(arg->champ_id)--;
	return (arg->champ_id);
}

t_champ			*read_input(int argc, char **args, t_arg *arg)
{
	t_champ	*champs;
	t_champ	*ichamp;
	int		flag_res;
	int		i;

	champs = NULL;
	i = 1;
	while (i < argc)
	{
		flag_res = set_flag(args, &i, arg, champs);
		if (flag_res == NOT_FLAG)
			ichamp = read_file(&champs, args[i]);
		if (flag_res == INVALID_FLAG || (flag_res == NOT_FLAG && !ichamp))
			terminate(&champs);
		if (flag_res == NOT_FLAG)
			ichamp->id = get_next_id(champs, arg);
		i++;
	}
	if (count_champs(champs) > MAX_PLAYERS)
	{
		ft_printf("Too many champions\n");
		terminate(&champs);
	}
	return (champs);
}
