/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
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

	if ((t_uint)read(fd, buf, code_len) != code_len) //	overfloat (code_len > MAX_INT)
	{
		ft_printf("Error: File %s has a code size that differ \
		from what its header says\n", filename);
		return (NULL);
	}
	if (code_len > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code \
		(%u bytes > %d bytes)\n", filename, code_len, CHAMP_MAX_SIZE);
		return (NULL);
	}
	code = (t_uchar*)ft_strdup((char*)buf);
	return (code);
}

static bool		read_codelen(int fd, char *filename, t_uint *code_len)
{
	t_uchar	buf[CODELEN_SIZE];

	if (read(fd, buf, CODELEN_SIZE) != CODELEN_SIZE)
	{
		ft_printf("Error: File %s is too small to be a champion\n", filename);
		return (false);
	}
	*code_len = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
	return (true);
}

static t_uchar	*read_string(int fd, char *filename, t_uint len)
{
	t_uchar	buf[len + 1];
	t_uchar	*string;

	ft_bzero(buf, len + 1);
	if (read(fd, buf, len) != len)
	{
		ft_printf("Error: File %s is too small to be a champion\n", filename);
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
		ft_printf("Error: File %s is too small to be a champion\n", filename);
		return (false);
	}
	magic_bytes = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	if (magic_bytes != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Error: File %s has an invalid header\n", filename);
		return (false);
	}
	return (true);
}

/*
**	'PROG_NAME_LENGTH + 4' means 'name + 4 null bytes'
**	as well as 'COMMENT_LENGTH + 4'
*/

bool			reading(t_champ **champs, int fd, char *filename)
{
	t_champ	*somechamp;
	t_uint	code_len;

	RET_CHECK(validate_header(fd, filename), false);
	//	adds somechamp to the champs list and sets all of the fileds to NULL
	//	will be freed up in terminate_input() with whole list
	somechamp = new_champ(champs);
	RET_CHECK(somechamp, false);
	somechamp->name = read_string(fd, filename, PROG_NAME_LENGTH + 4);
	RET_CHECK(somechamp->name, false);
	RET_CHECK(read_codelen(fd, filename, &code_len), false);
	somechamp->comment = read_string(fd, filename, COMMENT_LENGTH + 4);
	RET_CHECK(somechamp->comment, false);
	somechamp->code = read_code(fd, filename, code_len);
	RET_CHECK(somechamp->code, false);
	return (true);
}
