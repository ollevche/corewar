/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 19:05:45 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/05 19:05:46 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool		has_item(int target_type, t_file *head, int search_limit)
{
	int counter;

	if (head == NULL)
		return (false);
	counter = 0;
	while (head->next && counter < search_limit)
	{
		if (head->type == target_type)
			return (true);
		head = head->next;
		counter++;
	}
	return (false);
}

#define FREE_RET(F, R) { free(F); return (R); }

static char	*extract_str(int fd, char *line, int line_num, int ind)
{
	int		i;
	char	str;

	if (line[ind] != '"')
	{
		ft_printf("%s [%d, %d]\n", QUOTE_ERR, line_num, ind);
		return (NULL);
	}
	str = ft_strnew(0);
	i = ind + 1;
	while (line[i] != '"')
	{
		if (!line[i])
		{
			if (!(str = ft_strjoinfree(str, line + ind)))
				return (NULL);
			free(line);
			if (!(line = safe_gnl(fd)))
				break ;
			i = -1;
			ind = 0;
		}
		i++;
	}
	if ()
}

static int	extract_name(int fd, t_item **head, char *line, int line_num)
{
	int 	ind;
	char	command;
	char	*str;

	ind = skip_wspaces(line);
	command = cut_word(line);
	if (ft_strcmp(command, COMMENT_CMD_STRING))
		return (DEF_T);
	ind += ft_strlen(command);
	free(command);
	ind += skip_wspaces(line + ind);
	str = extract_str(fd, line, line_num, ind); // prints errors
	if (!str)
		return (ERR_T);
	if (!add_item(head, str, line_num, NAME_T))
		return (ERR_T);
	return (NAME_T);
}

t_item		*extract_header(int fd)
{
	t_item	*head;
	char	*line;
	int		last_read;
	int		line_num;

	head = NULL;
	line_num = 0;
	while ((line = safe_gnl(fd)))
	{
		// if (is_empty(line))
		// 	continue ;
		last_read = DEF_T;
		if (!has_item(NAME_T, head, 2))
			last_read = extract_name(fd, &head, line, &line_num); // adds item // returns DEF_T if it's not a name // prints error
		if (last_read == DEF_T && !has_item(COMM_T, head, 2))
			last_read = extract_comment(fd, &head, line, &line_num); // adds item // returns DEF_T if it's not a comment // prints error
		if (last_read == DEF_T || last_read == ERR_T)
			break ;
		if (has_item(NAME_T, head, 2) && has_item(COMM_T, head, 2))
			return (head);
		line_num++;
	}
	if (last_read == DEF_T)
		ft_printf("%S %d\n", NOHDR_ERR, line_num);
	SAFE_RET(&head, NULL);
}
