/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:32:31 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/17 15:32:32 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"
#include "fcntl.h"

int	main(int argc, char **args)
{
	t_champ	*champs;

	champs = read_input(argc, args);
	play_the_game(champs); // check for return type
	// print_result();

	// if (argc > 1)
	// 	ft_printf("%x\n", args[argc - 1][0]);
	// int fd = open("Gagnant.cor", O_RDONLY, 0);
	// unsigned char buff[1];
	// while (read(fd, buff, 1))
	// 	ft_printf("%x\t%c\n", buff[0], buff[0]);
	return (0);
}
