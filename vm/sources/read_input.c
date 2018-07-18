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

t_champ	*read_input(int argc, char **args)
{
	t_champ	*champs;
	t_uchar	*buffer;
	int		i;
	char	*err_mes;

	i = 1;
	while (i < argc)
	{
		if (validate_champ(args[i], &buffer, &err_mes)) // ft_strstr(args[i], ".cor") != NULL
			add_champ(champs, buffer);
		else if (!set_flag(args, &i))
		{
			free_champs(&champs);
			EXIT_M(err_mes);
		}
		ft_bzero(buffer, CHAMP_MAX_SIZE);
		i++;
	}
	return (champs);
}
