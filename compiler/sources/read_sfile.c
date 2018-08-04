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

static bool		check_endnl(int fd)
{
	char	c;

	lseek(fd, -1, SEEK_END);
	read(fd, &c, 1);
	if (c == '\n')
		return (true);
	ft_printf("%s %s\n", ENDLINE_ERR, ENDLINE_HINT);
	return (false);
}

static int		check_open(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_printf("%s %s\n", READ_ERR, filename);
	return (fd);
}

static t_item	*extract_content(int fd)
{
    char    *line;
    int     line_num;
    int     type;
    t_item  *head;

    line_num = 1;
	head = NULL;
    while ((line = safe_gnl(fd)))
	{
        type = syntactically_valid(line, line_num);
		if (type == ERR_TYPE || !add_item(&head, line, line_num, type))
            SAFE_RET(&head, NULL);
        line_num++;
	}
    return (head);
}

t_item			*read_sfile(char *filename)
{
	int		fd;
	t_item	*head;

	fd = check_open(filename);
	IF_RET(fd < 0, NULL);
	head = extract_content(fd);
	IF_RET(!head, NULL);
	IF_RET(!check_endnl(fd), NULL);
	close(fd);
	return (head);
}
