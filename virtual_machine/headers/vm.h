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
# include <stdint.h>

# define RET_CHECK(X, R) if (!(X)) return (R);

# define USAGE_STR		"we've not created usage text yet" // TODO: this

# define HEADER_SIZE	4
# define CODELEN_SIZE	4

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

//	bool op_func(t_session *game, t_champ *champs, t_process *executing_carry);

typedef struct			s_process
{
	t_uchar				regs[REG_NUMBER];
	t_uint				pc; // current position on the map
	bool				carry; // was last op successful
	t_uint				inactive; // inactive for N cycles required by op
	t_uchar				op_code; // current operation code
	t_uint				last_live; // cycle, when last live was called
	struct s_process	*next;
}						t_process;

typedef struct			s_champ
{
	t_process		*carrys;
	t_uchar			*name;
	t_uchar			*comment;
	t_uint			code_len;
	t_uchar			*code;
	t_uint			id;
	struct s_champ	*next;
}						t_champ;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	t_uint	cycle;
	t_uint	period_lives; // number of live calls in the last period
	int		cycle_to_die;
	t_uint	last_ctd; // last change of cycle_to_die
	t_champ	*last_alive;
	t_uint	total_champs;
}						t_session;

#endif
