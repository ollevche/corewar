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


# define USAGE_STR		"we've not created usage text yet" // TODO: this

# define HEADER_SIZE	4
# define CODELEN_SIZE	4
# define OP_COUNT		8 // original 16

/*
** FUNCTIONAL DEFINES ▽
*/

# define RET_CHECK(X, R) if (!(X)) return (R);
# define IS_REG(r) (r > 0 && r < REG_NUMBER)

/*
** DEFINES FOR READABILITY ▽
*/

# define LAST_LIVE		carry->last_live
# define LAST_ALIVE		game->last_alive
# define PERIOD_LIVES	game->period_lives
# define MAP 			game->map
# define PC				carry->pc
# define CYCLE			game->cycle
# define REGS			carry->regs
# define CARRY			carry->carry

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_carry
{
	t_uint			regs[REG_NUMBER];
	int				pc; // current position on the map
	bool			carry; // was last op successful
	int				inactive; // inactive for N cycles required by op
	t_uchar			op_code; // current operation code
	int				last_live; // cycle, when last live was called
	struct s_carry	*next;
}						t_carry;

typedef struct			s_champ
{
	t_uchar			*name;
	t_uchar			*comment;
	t_uint			code_len;
	t_uchar			*code;
	int				id;
	struct s_champ	*next;
}						t_champ;

/*
**	game state info
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	int			cycle;
	int			period_lives; // number of live calls in the last period
	int			cycle_to_die;
	int			last_ctd; // last change of cycle_to_die
	t_champ		*last_alive;
	t_carry	*carrys; // all of the carries
	int			carry_num; // number of carries in a session
	int			total_champs;
}						t_session;

/*
**	operation receives game (session), carrys (carries), head of champs (champ)
*/

typedef bool	(*t_operation)(t_session *g, t_carry *ca, t_champ *h);

typedef struct			s_op
{
	char	name[PROG_NAME_LENGTH];
	int		nb_params;
	char	params_type[3];
	int		id;
	int		cycles;
	char	description[50];
	int		codage;
	int		label_size;
	bool	ind_idx;
}						t_op;

extern const t_op		g_optab[18];

typedef struct			s_arg
{
	bool	is_visual;
	int		dump;
	int		champ_id;
}						t_arg;

#endif
