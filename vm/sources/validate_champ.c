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

//TODO: error management, CHAMP_MAX_SIZE is not max size of whole champion

#define TOO_SMALL " is too small to be a champion"
#define HEADER_SAYS " has a code size that differ from what its header says"

static bool	read_and_check(int fd, t_uchar *buffer, int len, char **err_mes)
{
	int bytes_read;

	bytes_read = read(fd, buffer, len);
	if (bytes_read != len)
	{
		*err_mes = ft_strjoin_nfree(*err_mes, TOO_SMALL, 0);
		return (false);
	}
	return (true);
}

static bool	validate_code(int fd, t_uchar *buffer, unsigned int code_len,
							char **err_mes)
{
	unsigned int bytes_read;

	if (code_len > CHAMP_MAX_SIZE)
	{
		*err_mes = ft_strjoin_nfree(*err_mes, " has too large a code (X bytes > 682 bytes)", 0);
		return (false);
	}
	bytes_read = (unsigned int)read(fd, buffer, code_len + 1);
	if (bytes_read != code_len)
	{
		*err_mes = ft_strjoin_nfree(*err_mes, HEADER_SAYS, 0);
		return (false);
	}
	return (true);
}

/*
**	'PROG_NAME_LENGTH + 4' means 'name + 4 null bytes'
**	as well as 'COMMENT_LENGTH + 4'
*/

static bool	validate_parts(int fd, t_uchar *buffer, char **err_mes)
{
	unsigned int	magic_bytes;
	int				read;
	unsigned int	code_len;

	if (!read_and_check(fd, buffer, HEADER_SIZE, err_mes))
		return (false);
	read = HEADER_SIZE;
	magic_bytes = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
	if (magic_bytes != COREWAR_EXEC_MAGIC)
	{
		*err_mes = ft_strjoin_nfree(*err_mes, " has an invalid header", 0);
		return (false);
	}
	if (!read_and_check(fd, buffer + read, PROG_NAME_LENGTH + 4, err_mes))
		return (false);
	read += PROG_NAME_LENGTH + 4;
	if (!read_and_check(fd, buffer + read, CODELEN_SIZE, err_mes))
		return (false);
	code_len = (buffer + read)[0] << 24 | (buffer + read)[1] << 16 | (buffer + read)[2] << 8 | (buffer + read)[3];
	read += CODELEN_SIZE;
	if (!read_and_check(fd, buffer + read, COMMENT_LENGTH + 4, err_mes))
		return (false);
	if (!validate_code(fd, buffer + read, code_len, err_mes))
		return (false);
	return (true);
}

bool		validate_champ(char *arg, t_uchar **buffer, char **err_mes)
{
	int		fd;
	bool	is_champ;

	if (!ft_strstr(arg, ".cor"))
		return (false);
	is_champ = false;		
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		*err_mes = ft_strjoin("Can't read source file ", arg);
		return (false);
	}
	*err_mes = ft_strjoin("Error: File ", arg);
	if ((*buffer = (t_uchar*)ft_strnew(CHAMP_MAX_SIZE)))
		is_champ = validate_parts(fd, *buffer, err_mes);
	close(fd);
	return (is_champ);
}
