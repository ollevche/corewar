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

static t_item*	read_sfile(char *filename)
{
	int		fd;
	char	*line;
	t_item	*head;
	t_item	*last;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		return (NULL);
	}
	head = NULL;
	last = NULL;
	while ((line = safe_gnl(fd)))
	{
		last = add_item(&head, line);
		if (!last)
			SAFE_RET(&head, NULL);
	}
	if (last->line[0] != 0) // if it's not an empty line
	{
		ft_printf("Syntax error - unexpected end of input \
(Perhaps you forgot to end with a newline ?)");
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
