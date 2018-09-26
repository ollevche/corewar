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

#define	HAS_ITEM(T, H) (get_item_by_type(T, H) ? true : false)

// TODO: refactor the func (3 star exercise)

static char	*extract_str(int fd, char **line, int *line_num, int ind)
{
	int		len;
	char	*str;

	if ((*line)[ind] != '"')
	{
		ft_printf("%s [%03d:%03d]\n", QUOTE_ERR, *line_num, ind + 1);
		return (NULL);
	}
	ind++; // at quote
	if (!(str = ft_strnew(0)))
		return (NULL);
	while ((*line)[ind] != '"') // all quotes are read
	{
		len = 0;
		while ((*line)[ind + len] && (*line)[ind + len] != '"') // end of line or quote
			len++;
		if (!(str = ft_strjoinfree(str, ft_strndup(*line + ind, len))))
			return (NULL);
		ind += len;
		if ((*line)[ind] == '"') // quote - break; end of line - read next line
			break ;
		free(*line);
		if (!(*line = safe_gnl(fd))) // there's no lines (quote still opened)
		{
			ft_printf("%s [%03d:%03d]\n", QUOTE_ERR, *line_num, ind + 1);
			free(str);
			return (NULL);
		}
		(*line_num)++;
		ind = 0;
		str = ft_strjoin_nfree(str, "\n", 0);
		if (!str)
			return (NULL);
	}
	ind++; // at the next char after the quote
	ind += skip_wspaces(*line + ind);
	trim_comments(*line + ind);
	if ((*line)[ind]) // check for an empty leftover of the line
	{
		ft_printf("%s [%03d:%03d] ('%s')\n", UNDEF_ERR, *line_num, ind + 1, str);
		free(str);
		return (NULL);
	}
	return (str);
}

static int	extract_command(int fd, t_item **head, char **line, int *line_num)
{
	int 	ind;
	int		type;
	char	*command;
	char	*str;

	ind = skip_wspaces(*line);
	command = cut_word(*line + ind);
	if (!ft_strcmp(command, NAME_CMD_STRING))
		type = NAME_T;
	else if (!ft_strcmp(command, COMMENT_CMD_STRING))
		type = COMM_T;
	else
	{
		ft_printf("%s [%03d:%03d] ('%s')\n", UNDEF_ERR, *line_num, ind + 1, command);
		free(command);
		return (ERR_T);
	}
	ind += ft_strlen(command);
	free(command);
	ind += skip_wspaces(*line + ind);
	str = extract_str(fd, line, line_num, ind); // prints errors
	if (!str || !add_item(head, str, *line_num, type))
		return (ERR_T);
	return (type);
}

static bool	has_doublings(t_item *head)
{
	int names;
	int comments;

	names = 0;
	comments = 0;
	while (head && names < 2 && comments < 2)
	{
		if (head->type == NAME_T)
			names++;
		if (head->type == COMM_T)
			comments++;
		head = head->next;
	}
	if (names > 1 || comments > 1)
		ft_printf("%s\n", HDR_DOUBL);
	return (names < 2 && comments < 2);
}

t_item		*extract_header(int fd)
{
	t_item	*head;
	char	*line;
	int		last_read;
	int		line_num;

	head = NULL;
	line_num = 0;
	last_read = DEF_T;
	while ((line = safe_gnl(fd)))
	{
		line_num++;
		if (!is_empty(line))
		{
			last_read = extract_command(fd, &head, &line, &line_num);
			if (last_read == DEF_T || last_read == ERR_T || !has_doublings(head))
				break ;
		}
		free(line);
		if (HAS_ITEM(NAME_T, head) && HAS_ITEM(COMM_T, head))
			return (head);
	}
	if (last_read != ERR_T)
		ft_printf("%s %d\n", NOHDR_ERR, line_num);
	free(line);
	SAFE_RET(&head, NULL); // it's error (no name or comment)
}
