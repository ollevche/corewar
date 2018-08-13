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
	ft_printf("%s %s %s\n",ERROR_M, ENDLINE_ERR, ENDLINE_HINT);
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

// static t_item	*extract_content(int fd)
// {
	// char	*line;
	// int		last_read;
	// int		line_num;
    // t_item  *head;

	// head = NULL;
	// line_num = 0;
	// while ((line = safe_gnl(fd)))
	// {
	// 	if (is_empty(line))
	// 		continue ;
	// 	last_read = DEF_T;
	// 	if (has_name(head) && has_comment(head))
	// 		last_read = extract_instruction(head, line, line_num);
	// 	if (last_read == DEF_T && !has_name(head))
	// 		last_read = extract_name(head, line, fd, &line_num); // returns DEF_T if it's not a name
	// 	if (last_read == DEF_T && !has_comment(head))
	// 		last_read = extract_comment(head, line, fd, &line_num); // returns DEF_T if it's not a comment
	// 	if (last_read == ERR_T || last_read == DEF_T)
	// 		SAFE_RET(&head, NULL);
	// 	line_num++;
	// }
    // return (head);
// }

t_item			*read_sfile(char *filename)
{
	int		fd;
	t_item	*head;

	fd = check_open(filename);
	IF_RET(fd < 0, NULL);
	head = extract_header(fd);
	IF_RET(!head, NULL);
	// extract_instructions(fd, head);
	IF_RET(!head, NULL);
	IF_RET(!check_endnl(fd), NULL);
	close(fd);
	return (head);
}
