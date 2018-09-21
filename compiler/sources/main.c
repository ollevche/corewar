/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:34:10 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/02 13:34:10 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**
**	notes:
**		permits non .s files
**		displays usage if no files provided
**		doesn't permit no code
**		doesn't permit no name or no comment
**		last line has to be empty ("\n")
**		permits "" as name or comment
**		checks name and comment by size
**		permits separating words by space and tab (no matter len, 0 including)
**		rule: one item per line
**		empty line is correct
**		doesn't check for code size (10k lines of code is ok)
**
**	bonus:
**		multiple files at a time
**
*/

void	fill_label_values(t_item *items);
const	t_op	g_optab[18] =
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

bool		compile(char *filename)
{
	t_item	*items;

	items = read_sfile(filename);
	if (!items)
		SAFE_RET(&items, false);
	if (!semantically_valid(items))
		SAFE_RET(&items, false);
	calculate_size(items);
	fill_label_values(items);
	if (!to_bytecode(items))
		SAFE_RET(&items, false);
	if (!write_corfile(filename, items))
		SAFE_RET(&items, false);
	SAFE_RET(&items, true);
}

int			main(int argc, char **args)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!compile(args[i]))
			ft_printf("%s %s\n", NOT_COMPILED_ERR, args[i]);
		i++;
	}
	// if (i == 1)
	// 	print_usage(); // TODO: usage
	return (0);
}
