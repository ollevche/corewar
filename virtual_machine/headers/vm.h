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

# define USAGE_STR		"we've not created usage text yet" // TODO: this

# define HEADER_SIZE	4
# define CODELEN_SIZE	4

typedef unsigned char	t_uchar;

typedef struct			s_process
{
	t_uchar				regs[REG_NUMBER];
	uint				pc;
	bool				carry;
	uint				inactive; // inactive for N cycles required by op
	t_uchar				op_code; // current operation code
	uint				lastLive; // NBR_LIVE is a sum of all live champs	
	struct s_process	*next;
}						t_process;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	uint	cycle;
	uint	period_lives;
	uint	cycle_to_die;
	uint	last_ctd;
	uint	total_champs;
}						t_session;

typedef struct			s_champ
{
	t_process		*carrys;
	t_uchar			*name;
	t_uchar			*comment;
	uint			code_len;
	t_uchar			*code;
	uint			id;
	struct s_champ	*next;
}						t_champ;

#endif
