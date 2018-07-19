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

char	*free_n_join(char *s1, char *s2, int f)
{
	char *tmp1;
	char *tmp2;
	char *ret;

	tmp2 = s2;
	tmp1 = s1;
	ret = ft_strjoin(s1, s2);
	if (f == 1)
		free(tmp1);
	if (f == 2)
		free(tmp2);
	if (f == 3)
	{
		free(tmp1);
		free(tmp2);
	}
	return (ret);
}

static bool	validate_header(int fd, t_uchar *buffer, char **err_mes)
{
	int				bytes_read;
	unsigned int	header;

	bytes_read = read(fd, buffer, HEADER_SIZE);
	if (bytes_read != HEADER_SIZE)
	{
		*err_mes = free_n_join(*err_mes, " is too small to be a champion", 1);
		return (false);
	}
	header = COREWAR_EXEC_MAGIC;
	if (buffer[3] == *(t_uchar*)(&header)
		&& buffer[2] == *((t_uchar*)(&header) + 1)
		&& buffer[1] == *((t_uchar*)(&header) + 2)
		&& buffer[0] == *((t_uchar*)(&header) + 3))
		return (true);
	*err_mes = free_n_join(*err_mes, " has an invalid header", 1);
	return (false);
}

bool		validate_champ(char *arg, t_uchar **buffer, char **err_mes)
{
	int		fd;
	bool	is_champ;

	if (!ft_strstr(arg, ".cor"))
		return (false);
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		*err_mes = ft_strjoin("Can't read source file ", arg);
		return (false);
	}
	*err_mes = ft_strjoin("Error: File ", arg);
	if ((*buffer = (t_uchar*)ft_strnew(CHAMP_MAX_SIZE)))
	{
		is_champ = true;
		is_champ = (is_champ ? validate_header(fd, *buffer, err_mes) : false);
		// is_champ = (is_champ ? validate_name(fd, *buffer, err_mes) : false);
		// is_champ = (is_champ ? validate_size(fd, *buffer, err_mes) : false);
		// is_champ = (is_champ ? validate_comment(fd, *buffer, err_mes) : false);
		// is_champ = (is_champ ? validate_code(fd, *buffer, err_mes) : false);
		return (is_champ);
	}
	close(fd);
	return (false);
}