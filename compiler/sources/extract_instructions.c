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

#define IF_FREE_RET(B, F, R) if (B) {free(F); return (R);}

static int	validate_arg(char *line, int i, int line_num)
{
	int		len;
	int		a;
	char	*arg;

	(void)line_num;
	i += skip_wspaces(line + i);
	arg = cut_word(line + i);
	len = ft_strlen(arg);
	if (len < 1)
	{
		ft_printf("TODO: expected arg error\n");
		IF_FREE_RET(true, arg, -1);
	}
	if (arg[len - 1] == SEPARATOR_CHAR)
		arg[--len] = '\0';
	if (arg[0] == REG_CHAR)
		if (ft_isdigit(arg[1]) && (!arg[2] || (ft_isdigit(arg[2]) && !arg[3])))
			return (i + len);
	a = 0;
	if (arg[a] == DIRECT_CHAR && arg[a + 1])
		a++;
	if (arg[a] == LABEL_CHAR && arg[a + 1])
		if (ft_check_str(arg + a + 1, LABEL_CHARS))
			return (i + len);
	if (ft_isnumber(arg + a))
		return (i + len);
	ft_printf("TODO: invalid arg error\n");
	return (-1);
}

static int	save_label(char *line, int line_num, t_item *head)
{
	int		i;

	i = skip_wspaces(line);
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (line[i] != LABEL_CHAR)
	{
		// ft_printf("TODO: undef token error\n"); // NOTE: there's no error if no label
		return (0);
	}
	add_item(&head, ft_strndup(line, i + 1), line_num, DEF_T);
	return (i + 1);
}

static int	validate_command(char *line, int i, int line_num)
{
	char	*command;
	int		j;

	(void)line_num;
	i += skip_wspaces(line + i);
	command = cut_word(line + i);
	j = 0;
	while (command[j] && ft_strchr(LABEL_CHARS, command[j]))
		j++;
	if (command[j])
		ft_printf("TODO: symbol isn't acceptable error\n");
	i = (command[j] ? -1 : i + j);
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
		i = validate_arg(line, i, line_num); // checks for empty arg
		IF_RET(i < 0, -1);
		i += skip_wspaces(line + i);
		if (line[i] != SEPARATOR_CHAR)
			break ;
		i++;
	}
	if (line[i])
		ft_printf("TODO: expected separator error\n");
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
