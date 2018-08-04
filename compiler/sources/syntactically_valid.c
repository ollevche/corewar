/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactically_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 12:53:05 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/04 12:53:06 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	err_leftover(char *line, int line_num, int pos)
{
	(void)line;
	(void)line_num;
	(void)pos;
	ft_printf("// TODO: print an error (LEX / SYN)\n");
	return (ERR_TYPE);
}

static int	check_opened_str(char *line, int line_num, int pos)
{
	int type;

	type = STR_ML_T;
	while (line[pos] && line[pos] != '"')
		pos++;
	if (line[pos] == '"')
	{
		type = STR_T;
		pos++;
	}
	pos += skip_wspaces(line + pos); // check
	if (line[pos] == '\0')
		return (type);
	return (err_leftover(line, line_num, pos));
}

static int	check_str(char *line, int line_num, int pos)
{
	pos += skip_wspaces(line + pos); // check
	if (line[pos] != '"')
	{
		err_leftover(line, line_num, pos);
		return (false);
	}
	return (check_opened_str(line, line_num, pos + 1));
}

static char	*cut_word(char *line) // check
{
	int		len;
	char	*word;

	len = count_nwspaces(line);
	word = ft_strndup(line, len);
	return (word);
}

static int	check_header(char *line, int line_num, int pos)
{
	char	*cmd;
	int		type;

	cmd = cut_word(line);
	type = ERR_TYPE;
	pos += ft_strlen(cmd) + 1;
	if (!ft_strcmp(NAME_CMD_STRING, cmd))
		type = check_str(line, line_num, pos) - 2; // '-2' means casting from STR type to NAME type
	else if (!ft_strcmp(COMMENT_CMD_STRING, cmd))
		type = check_str(line, line_num, pos) - 4; // '-4' means casting from STR type to COMMENT type
	else
		ft_printf("%s [%d:%d] %s \"%s\"\n", LEX_ERR, line_num, pos, NSTR, cmd);
	IF_RET(type < 0, ERR_TYPE); // because of (-2) and (-4)
	return (type);
}

static bool	is_multiline(int type)
{
	return (type == STR_ML_T || type == NAME_ML_T || type == COMM_ML_T);
}

int     	syntactically_valid(char *line, int line_num) // TODO: comments
{
	int			type;
	int			pos;
	static bool	expecting_str = 0;

	type = ERR_TYPE;
	pos = skip_wspaces(line);
	if (line[pos] == '\0')
		return (EMP_T);
	if (expecting_str)
		type = check_opened_str(line, line_num, 0);
	else if (line[pos] == '.')
		type = check_header(line, line_num, pos);
	// else
	// 	type = check_code(line, line_num, pos); // write
	if (is_multiline(type)) // write
		expecting_str = 1;
	else
		expecting_str = 0;
	return (type);
}
