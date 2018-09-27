/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 17:27:29 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/21 17:27:29 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*add_extension(char *filename)
{
	int		len;
	char	*new;

	len = ft_strlen(filename);
	if (filename[len - 2] == '.' && filename[len - 1] == 's')
		len -= 2;
	new = ft_strnew(len + 4);
	IF_RET(!new, false);
	ft_strcpy(new, filename);
	ft_strcpy(new + len, ".cor");
	return (new);
}

t_item		*write_header(int fd, t_item *items)
{
	t_item	*name;
	t_item	*comment;
	t_uchar	byte;

	name = get_item_by_type(NAME_T, items);
	comment = get_item_by_type(COMM_T, items);
	write(fd, "\x00\xea\x83\xf3", 4);
	write(fd, name->bytecode, name->size);
	write(fd, "\x00\x00\x00\x00", 4);
	byte = (g_codesize & 0xff000000) >> 24;
	write(fd, &byte, 1);
	byte = (g_codesize & 0xff0000) >> 16;
	write(fd, &byte, 1);
	byte = (g_codesize & 0xff00) >> 8;
	write(fd, &byte, 1);
	byte = g_codesize & 0xff;
	write(fd, &byte, 1);
	write(fd, comment->bytecode, comment->size);
	write(fd, "\x00\x00\x00\x00", 4);
	return (items->next->next);
}

bool		write_corfile(char *filename, t_item *items)
{
	int		fd;
	char	*updated_fname;

	updated_fname = add_extension(filename);
	ft_printf("Writing output program to %s\n", updated_fname);
	fd = open(updated_fname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(updated_fname);
	IF_RET(!fd, false);
	items = write_header(fd, items);
	while (items)
	{
		write(fd, items->bytecode, items->size);
		items = items->next;
	}
	close(fd);
	return (true);
}
