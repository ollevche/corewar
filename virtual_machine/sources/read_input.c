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

static int		ft_isnumber(char *str) // TODO: to lib
{
	if (*str == '-')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	return (*str == '\0');
}

static int		set_flag(char **args, int *i, t_arg *arg)
{
	if (!ft_strcmp(args[*i], "-dump"))
	{
		arg->dump = ft_atoi(args[++(*i)]);
		if (!ft_isnumber(args[*i]))
		{
			ft_printf("Flag -dump has invalid number\n");
			return (INVALID_FLAG);
		}
	}
	else if (!ft_strcmp(args[*i], "-n"))
	{
		arg->champ_id = ft_atoi(args[++(*i)]) + 1;
		if (!ft_isnumber(args[*i])) // TODO: check for duplicate ids
		{
			ft_printf("Flag -n has invalid number\n");
			return (INVALID_FLAG);
		}
	}
	else if (!ft_strcmp(args[*i], "-v"))
		arg->is_visual = true;
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
		flag_res = set_flag(args, &i, arg);
		if (flag_res == NOT_FLAG)
			ichamp = read_file(&champs, args[i]);
		if (flag_res == INVALID_FLAG || (flag_res == NOT_FLAG && !ichamp))
			terminate(&champs);
		if (flag_res == NOT_FLAG)
			ichamp->id = --(arg->champ_id);
		i++;
	}
	return (champs);
}
