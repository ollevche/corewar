/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:46:31 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/02 16:46:31 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_file(t_item *item)
{
	while (item)
	{
		ft_printf("%.3d\t%s\n", item->line_num, item->line);
		item = item->next;
	}
}

bool			compile(char *filename)
{
	t_item	*items;

	items = read_sfile(filename);
	if (!items)
		SAFE_RET(&items, false);
	print_file(items); // DEL
	// if (!to_bytecode(items))
	// 	SAFE_RET(&items, false);
	// if (!write_corfile(filename, items)) // ft_printf("Writing output program to %s\n", new_filename);
	// 	SAFE_RET(items, false);
	SAFE_RET(&items, true);
}
