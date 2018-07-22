/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:32:49 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/17 15:32:49 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libftprintf.h"
# include "op.h"
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

# define RET_CHECK(X, R) if (!(X)) return (R);

# define HEADER_SIZE 4
# define CODELEN_SIZE 4

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_process
{
	t_uchar	regs[REG_SIZE];
	t_uchar	pc;
	bool	carry;
	t_uchar	inactive; //	inactive for N cycles (if a command requires N cycles to be executed)
}						t_process;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	t_uchar	cycle;
	t_uchar lives;
	t_uchar cycle_to_die;
}						t_session;

/*
**	buff stores all of the champion file
**	name/comment/code is just a pointers to buff's parts
*/

typedef struct			s_champ
{
	t_process		**carrys;
	t_uchar			*name;
	t_uchar			*comment;
	t_uchar			*code;
	bool			alive;
	struct s_champ	*next;
}						t_champ;

#endif
