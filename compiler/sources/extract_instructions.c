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

#define FREE_RET(F, R) {free(F); return (R);}
#define IF_FREE_RET(B, F, R) if (B) FREE_RET(F, R)

static char	*cut_argument(char *line, int line_num, int i)
{
	char	*arg;
	int		len;

	len = 0;
	while (line[len] && !IS_WSPACE(line[len]) && line[len] != SEPARATOR_CHAR)
		len++;
	if (len < 1)
	{
		ft_printf("%s [%03d:%03d]\n", NO_ARG_ERR, line_num, i + 1);
		return (NULL);
	}
	arg = ft_strndup(line, len);
	return (arg);
}

static int	validate_arg(char *line, int i, int line_num)
{
	int		len;
	int		a;
	char	*arg;

	(void)line_num;
	i += skip_wspaces(line + i);
	arg = cut_argument(line + i, line_num, i);
	IF_RET(!arg, -1);
	len = ft_strlen(arg);
	if (arg[len - 1] == SEPARATOR_CHAR)
		arg[--len] = '\0';
	if (arg[0] == REG_CHAR)
		if (ft_isdigit(arg[1]) && (!arg[2] || (ft_isdigit(arg[2]) && !arg[3])))
			FREE_RET(arg, i + len);
	a = 0;
	if (arg[a] == DIRECT_CHAR && arg[a + 1])
		a++;
	if (arg[a] == LABEL_CHAR && arg[a + 1])
		if (ft_check_str(arg + a + 1, LABEL_CHARS))
			FREE_RET(arg, i + len);
	if (ft_isnumber(arg + a))
		FREE_RET(arg, i + len);
	ft_printf("%s [%03d:%03d] ('%s')\n", INVALID_ARG, line_num, i + 1, arg);
	free(arg);
	return (-1);
}

static int	validate_command(char *line, int i, int line_num)
{
	char	*command;
	bool	is_invalid;
	int		j;

	(void)line_num;
	i += skip_wspaces(line + i);
	command = cut_word(line + i);
	j = 0;
	while (command[j] && ft_strchr(LABEL_CHARS, command[j]))
		j++;
	is_invalid = command[j] && command[j] != '-' && command[j] != '%';
	if (is_invalid)
		ft_printf("%s [%03d:%03d] ('%s')\n", INVALID_COMM, line_num,
												i + j + 1, command);
	i = (is_invalid ? -1 : i + j);
	free(command);
	return (i);
}

static int	save_instruction(char *line, int i, int line_num, t_item *head)
{
	add_item(&head, ft_strdup(line + i), line_num, DEF_T);
	i += skip_wspaces(line + i);
	i = validate_command(line, i, line_num);
	IF_RET(i < 0, -1);
	while (true)
	{
		i += skip_wspaces(line + i);
		i = validate_arg(line, i, line_num);
		IF_RET(i < 0, -1);
		i += skip_wspaces(line + i);
		if (line[i] != SEPARATOR_CHAR)
			break ;
		i++;
	}
	if (line[i])
		ft_printf("%s [%03d:%03d]\n", NO_SEPARATOR, line_num, i);
	return (line[i] ? -1 : i);
}

bool		extract_instructions(int fd, t_item *head)
{
	char	*line;
	int		line_num;
	int		i;

	line_num = get_last(head)->line_num + 1;
	while ((line = safe_gnl(fd)))
	{
		i = 0;
		trim_comments(line);
		if (!is_empty(line))
			i = save_label(line, line_num, head);
		IF_FREE_RET(i < 0, line, false);
		if (!is_empty(line + i))
			i = save_instruction(line, i, line_num, head);
		IF_FREE_RET(i < 0, line, false);
		free(line);
		line_num++;
	}
	return (true);
}
