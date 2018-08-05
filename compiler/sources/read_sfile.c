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

bool	extract_header(int fd, t_item **head)
{
	// int		total_types;
	// char	*line;
	// char	*str;
	// int		type;

	// total_types = 0;
	// while ((line = safe_gnl(fd)) && total_types < (NAME_T + COMM_T))
	// {
	// 	type = extract_header_item(line, fd, &str); // validates all the line ("          .command        '\n       some str   \n '      ")
	// 	if (type != NAME_T && type != COMM_T)
	// 		return (false);
	// 	if (!add_item(head, str, -1, type))
	// 		return (false);
	// 	total_types += type;
	// }
	// if (total_types != NAME_T + COMM_T)
	// 	return (false);
	// return (true);
}

static t_item	*extract_content(int fd)
{
	char	*line;
	int		last_read;
	int		line_num;
    t_item  *head;

	head = NULL;
	line_num = 0;
	while ((line = safe_gnl(fd)))
	{
		if (is_empty(line))
			continue ;
		last_read = DEF_T;
		if (has_name(head) && has_comment(head))
			last_read = extract_instruction(head, line, line_num);
		if (last_read == DEF_T && !has_name(head))
			last_read = extract_name(head, line, fd, &line_num);
		if (last_read == DEF_T && !has_comment(head))
			last_read = extract_comment(head, line, fd, &line_num);
		if (last_read == ERR_T || last_read == DEF_T)
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
