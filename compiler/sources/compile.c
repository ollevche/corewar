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

/*
**	should read byte by byte and save items only
**	without any whitespaces and trash lines (comments and empty lines)
*/

static t_item	*read_sfile(char *filename)
{
	int		fd;
	char	*line;
	t_item	*head;
	t_item	*last;
	int		line_num;

	head = NULL;
	last = NULL;
	line_num = 1;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		return (NULL);
	}
	while ((line = safe_gnl(fd)))
		if (!(last = add_item(&head, line, line_num++)))
			SAFE_RET(&head, NULL);
	// if (last->line[0] != 0) // if it's not an empty line
	// {
	// 	ft_printf("%s %s\n", ENDLINE_ERR, ENDLINE_HINT);
	// 	SAFE_RET(&head, NULL);
	// }
	close(fd);
	return (head);
}

// static bool		is_valid(t_item *head)
// {
// 	t_item	*iter;

// 	iter = head;
// 	while (iter)
// 	{
// 		if (!empty_line(iter))
// 			if (!name(iter) && !comment(iter))
// 				if (!label(iter) && !command(iter))
// 					return (false);
// 		iter = iter->next;
// 	}
// 	return (true);
// }

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
	// if (!is_valid(items))
	// 	SAFE_RET(&items, false);
	// if (!to_bytecode(items))
	// 	SAFE_RET(&items, false);
	// if (!write_corfile(filename, items)) // ft_printf("Writing output program to %s\n", new_filename);
	// 	SAFE_RET(items, false);
	SAFE_RET(&items, true);
}
