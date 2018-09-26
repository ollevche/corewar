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

/*
**	standard info block about operations
*/

const t_op	g_optab[18] =
{
	{"", 0, {0}, 0, 0, "", 0, 0, false},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, false},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, true},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, true},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, false},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, false},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, false},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, false},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, false},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, false},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, true},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, true},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, false},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, false},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, true},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, false},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, false},
	{"", 0, {0}, 0, 0, "", 0, 0, false}
};

void		terminate(t_champ **champs)
{
	free_champs(champs);
	if (errno)
		perror("Default error");
	exit(EXIT_FAILURE);
}

static void	init_arg(t_arg *arg)
{
	arg->is_visual = false;
	arg->log = false;
	arg->dump = -1;
	arg->champ_id = -1;
}

int			main(int argc, char **args)
{
	t_champ	*champs;
	t_champ	*winner;
	t_arg	arg;

	init_arg(&arg);
	champs = read_input(argc, args, &arg);
	if (!champs)
		display_usage();
	display_contestants(champs, &arg);
	winner = play_the_game(champs, &arg);
	if (!winner)
		terminate(&champs);
	display_winner(winner, &arg);
	free_champs(&champs);
	return (0);
}
