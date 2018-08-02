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

#define SAFE_RET(I, R) { free_items(I); return (R); }

static t_item	*read_sfile(char *filename)
{
	int		fd;
	char	*line;
	t_item	*head;
	t_item	*last;

	head = NULL;
	last = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		return (NULL);
	}
	while ((line = safe_gnl(fd)))
		if (!(last = add_item(&head, line)))
			SAFE_RET(&head, NULL);
	if (last->line[0] != 0) // if it's not an empty line
	{
		ft_printf("%s %s\n", ENDLINE_ERR, ENDLINE_HINT);
		SAFE_RET(&head, NULL);
	}
	return (head);
}

bool			compile(char *filename)
{
	t_item	*items;

	items = read_sfile(filename);
	if (!items)
		SAFE_RET(&items, false);
	if (!is_valid(items))
		SAFE_RET(&items, false);
	// if (!to_bytecode(items))
	// 	SAFE_RET(&items, false);
	// if (!write_corfile(filename, items)) // ft_printf("Writing output program to %s\n", new_filename);
	// 	SAFE_RET(items, false);
	SAFE_RET(&items, true);
}
