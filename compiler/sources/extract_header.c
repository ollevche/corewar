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

#define HAS_ITEM(T, H) (get_item_by_type(T, H) ? true : false)

static int	extract_str_in_cycle(char **line, int *ind, char **str)
{
	int		len;

	len = 0;
	while ((*line)[*ind + len] && (*line)[*ind + len] != '"')
		len++;
	if (!(*str = ft_strjoinfree(*str, ft_strndup(*line + *ind, len))))
		return (0);
	*ind += len;
	if ((*line)[*ind] == '"')
		return (2);
	free(*line);
	return (1);
}

static char	*extract_str(int fd, char **line, int *line_num, int ind)
{
	char	*str;
	int		in_cycle;

	if ((*line)[ind] != '"' && show_err(QUOTE_ERR, *line_num, ind, 0))
		return (NULL);
	if (ind++ && !(str = ft_strnew(0)))
		return (NULL);
	while ((*line)[ind] != '"')
	{
		if ((in_cycle = extract_str_in_cycle(&(*line), &ind, &str)) == 0)
			return (NULL);
		else if (in_cycle == 2)
			break ;
		if (!(*line = safe_gnl(fd)) && show_err(QUOTE_ERR, *line_num, ind, 0))
			return (NULL);
		(*line_num)++;
		ind = 0;
		if ((str = ft_strjoin_nfree(str, "\n", 0)) == NULL)
			return (NULL);
	}
	ind += skip_wspaces(*line + ind + 1) + 1;
	trim_comments(*line + ind);
	if ((*line)[ind] && show_err(UNDEF_ERR, *line_num, ind, &str))
		return (NULL);
	return (str);
}

static int	extract_command(int fd, t_item **head, char **line, int *line_num)
{
	int		ind;
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
		show_err(UNDEF_ERR, *line_num, ind + 1, &command);
		return (ERR_T);
	}
	ind += ft_strlen(command);
	free(command);
	ind += skip_wspaces(*line + ind);
	str = extract_str(fd, line, line_num, ind);
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
	int		last_rd;
	int		line_num;

	head = NULL;
	line_num = 0;
	last_rd = DEF_T;
	while ((line = safe_gnl(fd)) && ++line_num)
	{
		trim_comments(line);
		if (!is_empty(line))
		{
			last_rd = extract_command(fd, &head, &line, &line_num);
			if (last_rd == DEF_T || last_rd == ERR_T || !has_doublings(head))
				break ;
		}
		free(line);
		if (HAS_ITEM(NAME_T, head) && HAS_ITEM(COMM_T, head))
			return (head);
	}
	if (last_rd != ERR_T)
		ft_printf("%s %d\n", NOHDR_ERR, line_num);
	free(line);
	SAFE_RET(&head, NULL);
}
