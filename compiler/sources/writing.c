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

bool		write_corfile(char *filename, t_item *items)
{
	int		fd;
	char	*updated_fname;

	updated_fname = add_extension(filename);
	ft_printf("Writing output program to %s\n", updated_fname);
	free(updated_fname);
	fd = open(updated_fname, O_WRONLY | O_TRUNC | O_CREAT);
	IF_RET(!fd, false);
	while (items)
	{
		if (items->type == NAME_T || items->type == COMM_T) // TODO: write to bytecode
			write(fd, items->line, items->size);
		else if (items->type > 0 && items->type < 17)
			write(fd, items->bytecode, items->size);
		items = items->next;
	}
	close(fd);
	return (true);
}
