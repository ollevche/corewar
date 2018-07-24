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

// TODO: check all malloc calls for null

void	terminate(void)
{
	if (errno)
		perror("Default error");
	exit(EXIT_FAILURE);
}

void	display_usage(char *usage_txt)
{
	ft_printf("%s\n", usage_txt);
	terminate();
}

int		main(int argc, char **args)
{
	t_champ	*champs;
	t_champ	*winner;

	champs = read_input(argc, args);
	if (!champs)
		display_usage(USAGE_STR);
	winner = play_the_game(champs);
	if (!winner)
		terminate();
	// print_result(winner);
	free_champs(&champs);
	return (0);
}
