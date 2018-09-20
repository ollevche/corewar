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

static bool	is_valid_arg(char *arg, bool *is_last)
{
	int len;

	len = ft_strlen(arg);
	*is_last = arg[len - 1] != SEPARATOR_CHAR;
	if (!*is_last)
		arg[len - 1] = '\0';
	if (*arg == REG_CHAR)
		return (ft_isdigit(arg[1]) && (!arg[2]
										|| (ft_isdigit(arg[2]) && !arg[3])));
		if (*arg == DIRECT_CHAR) // norme
		arg++;
	if (!*arg)
		return (false);
	if (*arg == LABEL_CHAR)
		return (ft_check_str(arg + 1, LABEL_CHARS));
	return (ft_isnumber(arg));
}

static bool	is_valid_name(char *line, int line_num, int *i)
{
	char	*name;
	bool	is_valid;

	name = cut_word(line);
	is_valid = true;
	if (!ft_check_str(name, LABEL_CHARS))
	{
		if (name[ft_strlen(name) - 1] != LABEL_CHAR)
			ft_printf("%s %s [%d:%d] ('%s')\n",
					ERROR_M, SYNTAX_ERR, line_num, *i + 1, name);
		is_valid = false;
	}
	else
		*i += ft_strlen(name);
	free(name);
	return (is_valid);
}

static bool	valid_separator(bool is_last, char *str, int line_num, int i)
{
	if (is_last && str)
	{
		ft_printf("%s %s [%d:%d] ('%s')\n",
				ERROR_M, SYNTAX_ERR, line_num, i + 1, str ? str : "");
		ft_memdel((void**)&str);
		return (false);
	}
	if (!is_last) // TODO: improve it
	{
		ft_printf("%s %s [%d:%d] ('%s')\n",
				ERROR_M, SYNTAX_ERR, line_num, i + 1, str ? str : "");
		return (false);
	}
	return (true);
}

static bool	is_valid_label(char *line, int line_num, int i) // TODO: improve it
{
	char	*label;
	char	*str;
	bool	is_valid;
	int		len;

	label = cut_word(line);
	is_valid = true;
	len = ft_strlen(label);
	if (label[len - 1] != LABEL_CHAR)
		is_valid = false;
	else
	{
		label[len - 1] = '\0';
		is_valid = ft_check_str(label + 1, LABEL_CHARS);
	}
	str = cut_word(line + len + skip_wspaces(line + len));
	if (is_valid)
		is_valid = (str ? false : true);
	if (!is_valid)
		ft_printf("%s %s [%d:%d] ('%s')\n", ERROR_M, SYNTAX_ERR, line_num, i + 1, label);
	free(str);
	free(label);
	return (is_valid);
}

static bool	syntactically_valid(char *line, int line_num)
{
	char	*str;
	bool	is_valid;
	bool	is_last;
	int		i;

	i = skip_wspaces(line);
	IF_RET(!is_valid_name(line + i, line_num, &i), is_valid_label(line + i, line_num, i));
	i += skip_wspaces(line + i);
	is_valid = true;
	is_last = false;
	while (is_valid && (str = cut_word(line + i)) && !is_last)
	{
		if (!is_valid_arg(str, &is_last))
			is_valid = false;
		i += (is_valid ? ft_strlen(str) + 1 : 0);
		i += (is_valid ? skip_wspaces(line + i) : 0);
		ft_memdel((void**)&str);
	}
	if (!is_valid) // TODO: improve it
		ft_printf("%s %s [%d:%d]\n", ERROR_M, SYNTAX_ERR, line_num, i + 1);
	else if (!valid_separator(is_last, str, line_num, i))
		is_valid = false;
	return (is_valid);
}

bool		extract_instructions(int fd, t_item *head)
{
	char	*line;
	int		line_num;

	line_num = get_last(head)->line_num + 1;
	while ((line = safe_gnl(fd)))
	{
		trim_comments(line);
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
	return (true);
}
