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

# define USAGE_STR		"we've not created usage text yet"

# define HEADER_SIZE	4
# define CODELEN_SIZE	4

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_process
{
	t_uchar				regs[REG_NUMBER];
	t_uint				pc;
	bool				carry;
	t_uint				inactive; // inactive for N cycles required by op
	t_uchar				op_code; // current operation code
	struct s_process	*next;
}						t_process;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	t_uint	cycle;
	t_uint	period_lives;
	t_uint	cycle_to_die;
	t_uint	total_champs;
}						t_session;

typedef struct			s_champ
{
	t_process		*carrys;
	t_uchar			*name;
	t_uchar			*comment;
	t_uint			code_len;
	t_uchar			*code;
	bool			alive;
	t_uint			id;
	struct s_champ	*next;
}						t_champ;

#endif
