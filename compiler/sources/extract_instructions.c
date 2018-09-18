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

static bool	ft_check_str(char *str, char *valid)
{
	if (!str)
		return (false);
	while (*str && ft_strrchr(valid, *str))
		str++;
	if (*str)
		return (false);
	return (true);
}

static bool	is_valid_arg(char *arg, int line_num, int i)
{
	
}

static bool	is_valid_name(char *line, int line_num, int *i)
{
	char	*name;
	bool	is_valid;

	name = cut_word(line);
	is_valid = true;
	if (!ft_check_str(str, LABEL_CHARS))
	{
		ft_printf("%s %s [%d:%d] ('%s')\n"
			ERROR_M, INVALID_COMM, line_num, *i + 1, name);
		is_valid = false;
	}
	*i += ft_strlen(name);
	free(name);
	return (is_valid);
}

static bool	syntactically_valid(char *line, int line_num)
{
	char	*str;
	bool	is_valid;
	int		i;
	int		j;

	i = skip_wspaces(line);
	IF_RET(!is_valid_name(line + i, line_num, &i), false);
	i += skip_wspaces(line + i);
	is_valid = true;
	while (is_valid && (str = cut_word(line + i)))
	{
		if (!is_valid_arg(str, line_num, i))
			is_valid = false;
		i += ft_strlen(str);
		i += skip_wspaces(line + i);
		free(str);
	}
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
