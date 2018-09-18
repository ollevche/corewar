/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:05:54 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/18 15:05:54 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	syntactically_valid(char *line, int line_num)
{
	//TODO: this
	(void)line;
	return (false);
}

bool		extract_instructions(int fd, t_item *head)
{
	char	*line;
	int		line_num;

	line_num = get_last(head)->line_num + 1;
	while ((line = safe_gnl(fd)))
	{
		if (!is_empty(line))
		{
			add_item(&head, line, line_num, DEF_T);
			if (!syntactically_valid(line, line_num))
				return (false);
		}
		else
			free(line);
		line_num++;
	}
}
