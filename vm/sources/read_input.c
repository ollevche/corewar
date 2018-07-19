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

bool	set_flag(char **args, int *i)
{
	(void)args;
	(void)i;	
	return (false);
}

void	add_champ(t_champ **champs, t_uchar *buffer)
{
	(void)champs;
	(void)buffer;
	ft_printf("Hello, valid champ\n");
	for (int i = 0; i < CHAMP_MAX_SIZE; i++)
		ft_printf("%x\t%c\n", buffer[i], buffer[i]);
}

t_champ	*read_input(int argc, char **args)
{
	t_champ	*champs;
	t_uchar	*buffer;
	int		i;
	char	*err_mes;

	champs = NULL;
	i = 1;
	while (i < argc)
	{
		if (validate_champ(args[i], &buffer, &err_mes))
			add_champ(&champs, buffer);
		else if (!set_flag(args, &i))
		{
			// free_champs(&champs);
			EXIT_M(err_mes);
		}
		ft_bzero(buffer, CHAMP_MAX_SIZE);
		// free(err_mes);
		i++;
	}
	return (champs);
}
