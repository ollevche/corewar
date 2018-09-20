/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:55:26 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/03 14:55:27 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define IF_CLOSE_RET(B, F, R) if (B) {close(F); return (R);}

static bool		check_endnl(int fd)
{
	char	c;

	lseek(fd, -1, SEEK_END);
	read(fd, &c, 1);
	if (c == '\n')
		return (true);
	ft_printf("%s %s %s\n", ERROR_M, ENDLINE_ERR, ENDLINE_HINT);
	return (false);
}

static int		check_open(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_printf("%s %s %s\n", ERROR_M, READ_ERR, filename);
	return (fd);
}

t_item			*read_sfile(char *filename)
{
	int		fd;
	t_item	*head;

	fd = check_open(filename);
	IF_CLOSE_RET(fd < 0, fd, NULL);
	head = extract_header(fd);
	IF_CLOSE_RET(!head, fd, NULL);
	IF_CLOSE_RET(!extract_instructions(fd, head), fd, NULL);
	if (!check_endnl(fd))
		free_items(&head);
	close(fd);
	return (head);
}
