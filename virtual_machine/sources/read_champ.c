/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 11:36:54 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/19 11:36:54 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

static t_uchar	*read_code(int fd, char *filename, t_uint code_len)
{
	t_uchar	buf[CHAMP_MAX_SIZE + 1];
	t_uchar	*code;
	int		read_ret;

	read_ret = read(fd, buf, code_len + 1);
	RET_CHECK(read_ret >= 0, NULL);
	if ((t_uint)read_ret != code_len)
	{
		if (!errno)
			ft_printf("Error: File %s has a code size that differ \
from what its header says\n", filename);
		return (NULL);
	}
	if (code_len > CHAMP_MAX_SIZE)
	{
		if (!errno)
			ft_printf("Error: File %s has too large a code \
(%u bytes > %d bytes)\n", filename, code_len, CHAMP_MAX_SIZE);
		return (NULL);
	}
	code = ft_memalloc(CHAMP_MAX_SIZE + 1);
	RET_CHECK(code, NULL);
	ft_memcpy(code, buf, CHAMP_MAX_SIZE + 1);
	return (code);
}

static bool		read_codelen(int fd, char *filename, t_uint *code_len)
{
	t_uchar	buf[CODELEN_SIZE];

	if (read(fd, buf, CODELEN_SIZE) != CODELEN_SIZE)
	{
		if (!errno)
			ft_printf("Error: File %s is too small to be a champion\n",
																	filename);
		return (false);
	}
	*code_len = ft_byte_to_uint(buf[0], buf[1], buf[2], buf[3]);
	return (true);
}

static t_uchar	*read_string(int fd, char *filename, t_uint len)
{
	t_uchar	buf[len + 1];
	t_uchar	*string;

	ft_bzero(buf, len + 1);
	if (read(fd, buf, len) != len)
	{
		if (!errno)
			ft_printf("Error: File %s is too small to be a champion\n",
																	filename);
		return (NULL);
	}
	string = (t_uchar*)ft_strdup((char*)buf);
	return (string);
}

static bool		validate_header(int fd, char *filename)
{
	t_uint	magic_bytes;
	t_uchar	buf[HEADER_SIZE];

	if (read(fd, buf, HEADER_SIZE) != HEADER_SIZE)
	{
		if (!errno)
			ft_printf("Error: File %s is too small to be a champion\n",
																	filename);
		return (false);
	}
	magic_bytes = ft_byte_to_uint(buf[0], buf[1], buf[2], buf[3]);
	if (magic_bytes != COREWAR_EXEC_MAGIC)
	{
		if (!errno)
			ft_printf("Error: File %s has an invalid header\n", filename);
		return (false);
	}
	return (true);
}

/*
**	'PROG_NAME_LENGTH + 4' means 'name + 4 null bytes'
**	as well as 'COMMENT_LENGTH + 4'
*/

t_champ			*read_champ(t_champ **champs, int fd, char *filename)
{
	t_champ	*somechamp;

	RET_CHECK(validate_header(fd, filename), NULL);
	somechamp = new_champ(champs);
	RET_CHECK(somechamp, NULL);
	somechamp->name = read_string(fd, filename, PROG_NAME_LENGTH + 4);
	RET_CHECK(somechamp->name, NULL);
	RET_CHECK(read_codelen(fd, filename, &(somechamp->code_len)), NULL);
	somechamp->comment = read_string(fd, filename, COMMENT_LENGTH + 4);
	RET_CHECK(somechamp->comment, NULL);
	somechamp->code = read_code(fd, filename, somechamp->code_len);
	RET_CHECK(somechamp->code, NULL);
	return (somechamp);
}
