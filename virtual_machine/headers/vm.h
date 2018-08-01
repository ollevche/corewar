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

//TODO: "Yes, the last born (youngest) champion plays first." from 'VIII.3 Champion’s execution'

# define HEADER_SIZE	4
# define CODELEN_SIZE	4
# define OP_COUNT		1 // original 16

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_process
{
	t_uchar				regs[REG_NUMBER];
	int					pc; // current position on the map
	bool				carry; // was last op successful
	int					inactive; // inactive for N cycles required by op
	t_uchar				op_code; // current operation code
	int					last_live; // cycle, when last live was called
	struct s_process	*next;
}						t_process;

typedef struct			s_champ
{
	t_process		*carrys;
	t_uchar			*name;
	t_uchar			*comment;
	t_uint			code_len;
	t_uchar			*code;
	int				id; // TODO: should be negative (test: live %-1)
	struct s_champ	*next;
}						t_champ;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	int		cycle;
	int		period_lives; // number of live calls in the last period
	int		cycle_to_die;
	int		last_ctd; // last change of cycle_to_die
	t_champ	*last_alive;
	int		process_num;
	int		total_champs;
}						t_session;

//	bool op_func(t_session *game, t_champ *champs, t_process *executing_carry);
typedef bool (*t_operation)(t_session *g, t_champ *c, t_process *ca, t_champ *h);

#endif
