/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 11:36:54 by dpozinen          #+#    #+#             */
/*   Updated: 2018/07/19 11:36:54 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

// #define HEADER_SAYS " has a code size that differ from what its header says"

// static bool	validate_code(int fd, t_uchar *buffer, t_uint code_len,
// 							char **err_mes)
// {
// 	t_uint bytes_read;

// 	if (code_len > CHAMP_MAX_SIZE)
// 	{
// 		*err_mes = ft_strjoin_nfree(*err_mes, " has too large a code (X bytes > 682 bytes)", 0);
// 		return (false);
// 	}
// 	bytes_read = (t_uint)read(fd, buffer, code_len + 1);
// 	if (bytes_read != code_len)
// 	{
// 		*err_mes = ft_strjoin_nfree(*err_mes, HEADER_SAYS, 0);
// 		return (false);
// 	}
// 	return (true);
// }

/*
**	'PROG_NAME_LENGTH + 4' means 'name + 4 null bytes'
**	as well as 'COMMENT_LENGTH + 4'
*/

t_uchar	*read_comment(int fd, char *filename)
{
	t_uchar	buf[COMMENT_LENGTH + 4 + 1];
	t_uchar	*comment;

	ft_bzero(buf, COMMENT_LENGTH + 4 + 1);
	if (read(fd, buf, COMMENT_LENGTH + 4) != COMMENT_LENGTH + 4)
	{
		ft_printf("Error: File %s is too small to be a champion\n", filename);
		return (NULL);
	}
	comment = ft_strdup(buf);
	return (comment);
}

t_uint	read_codelen(int fd, char *filename)
{
	t_uchar	buf[CODELEN_SIZE];
	t_uint	code_len;

	if (read(fd, buf, CODELEN_SIZE) != CODELEN_SIZE)
	{
		ft_printf("Error: File %s is too small to be a champion\n", filename);
		return (0);
	}
	code_len = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
	return (code_len);
}

t_uchar	*read_name(int fd, char *filename)
{
	t_uchar	buf[PROG_NAME_LENGTH + 4 + 1];
	t_uchar	*name;

	ft_bzero(buf, PROG_NAME_LENGTH + 4 + 1);
	if (read(fd, buf, PROG_NAME_LENGTH + 4) != PROG_NAME_LENGTH + 4)
	{
		ft_printf("Error: File %s is too small to be a champion\n", filename);
		return (NULL);
	}
	name = ft_strdup(buf);
	return (name);
}

bool	validate_header(int fd, char *filename)
{
	t_uint	magic_bytes;
	t_uchar			buf[HEADER_SIZE];

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

// "Error: File *filename* *error message*"

bool	reading(t_champ *champs, int fd)
{
	t_champ			*somechamp;
	t_uint	code_len;
	
	RET_CHECK(validate_header(fd), false);
	//	adds somechamp to the champs list and sets all of the fileds to NULL
	//	will be freed up in terminate_input() with whole list
	somechamp = new_champ(champs);
	RET_CHECK(somechamp, false);
	somechamp->name = read_name(fd, filename);
	RET_CHECK(somechamp->name, false);
	code_len = read_codelen(fd, filename);
	somechamp->comment = read_comment(fd, filename);
	RET_CHECK(somechamp->comment, false);
	somechamp->code = read_code(fd, filename, code_len);
	RET_CHECK(somechamp->code, false);
	return (true);
}

bool	read_champ(t_champ *champs, char *filename)
{
	int		fd;
	bool	is_champ;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		return (false);
	}
	is_champ = reading(champs, fd);
	close(fd);
	return (is_champ);
}
