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

static void	print_file(t_item *item)
{
	while (item)
	{
		ft_printf("%.3d\t%s\n", item->line_num, item->line);
		item = item->next;
	}
}

bool		compile(char *filename)
{
	t_item	*items;

	items = read_sfile(filename);
	if (!items)
		SAFE_RET(&items, false);
	// if (!semantically_valid(items))
	// 	SAFE_RET(&items, false);
	print_file(items); // DEL
	// if (!to_bytecode(items))
	// 	SAFE_RET(&items, false);
	// fill_labels(items);
	// if (!write_corfile(filename, items)) // ft_printf("Writing output program to %s\n", new_filename);
	// 	SAFE_RET(items, false);
	SAFE_RET(&items, true);
}
//TODO: init structs properly
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
	return (0);
}
