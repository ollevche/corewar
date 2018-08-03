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

static bool	check_endnl(int fd)
{
	char	c;

	lseek(fd, -1, SEEK_END);
	read(fd, &c, 1);
	if (c == '\n')
		return (true);
	ft_printf("%s %s\n", ENDLINE_ERR, ENDLINE_HINT);
	return (false);
}

static bool	read_header(int fd, t_file **head, int line_num)
{
	char	*line;
	char	*token;
	int		type;
	t_item	*item;

	skip_wspaces(fd);
	token = read_token(fd, line_num + 1);
	IF_RET(!token, false);
	type = (token[0] == '.') ? 0 : -1;
	type = (!ft_strcmp(NAME_CMD_STRING, token)) ? NAME_T : type;
	type = (!ft_strcmp(COMMENT_CMD_STRING, token)) ? COMMENT_T : type;
	if (type == 0)
		ft_printf();
	free(token);
	skip_wspaces(fd);
	line = read_quotes(fd, line_num + 1);
	IF_RET(!line, false);
	add_item(head, line, line_num + 1)
}

t_item		*read_sfile(char *filename)
{
	int		fd;
	t_item	*head;

	head = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s %s\n", READ_ERR, filename);
		return (NULL);
	}
	IF_RET(!read_header(fd, &head, 0), NULL);
	// IF_RET(!read_content(fd, head), NULL);
	IF_RET(!check_endnl(fd), NULL);
	close(fd);
	return (head);
}
