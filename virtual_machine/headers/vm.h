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

# define HEADER_SIZE	4
# define CODELEN_SIZE	4
# define OP_COUNT		16
# define DEF_OPCODE		17

/*
** FUNCTIONAL DEFINES ▽
*/

# define RET_CHECK(X, R) if (!(X)) return (R);
# define IS_REG(r) (r > 0 && r <= REG_NUMBER)
# define JMP (lpc - PC)
# define CHK_MV(x) if (!x) {update_position(carry, JMP + 1); return (1);}
# define MAPVAL(p, n) MAP[move_pc(p, n)]
# define OP_ATYP(c, i)	g_optab[c].params_type[i]

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

# define TYP1 args[0][0]
# define TYP2 args[0][1]
# define TYP3 args[0][2]
# define VAL1 args[1][0]
# define VAL2 args[1][1]
# define VAL3 args[1][2]

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

/*
**	int				pc; // current position on the map
**	bool			carry; // was last op successful
**	int				inactive; // inactive for N cycles required by op
**	t_uchar			op_code; // current operation code
**	int				last_live; // cycle, when last live was called
**	int				champ; // 'father' champ
*/

typedef struct			s_carry
{
	t_uint			regs[REG_NUMBER];
	int				pc;
	bool			carry;
	int				inactive;
	t_uchar			op_code;
	int				last_live;
	int				champ;
	struct s_carry	*next;
}						t_carry;

typedef struct			s_champ
{
	t_uchar			*name;
	t_uchar			*comment;
	t_uint			code_len;
	t_uchar			*code;
	int				id;
	int				period_lives;
	struct s_champ	*next;
}						t_champ;

typedef struct			s_arg
{
	bool	is_visual;
	bool	log;
	int		dump;
	int		champ_id;
}						t_arg;

/*
**	game state info
**
**	int		spot_map[MEM_SIZE]; // a node stores owners id
**	int		cycle;
**	int		period_lives; // number of live calls in the last period
**	int		cycle_to_die;
**	int		last_ctd; // last change of cycle_to_die
**	t_champ	*last_alive;
**	t_carry	*carries; // all of the carries
**	int		carry_num; // number of carries in a session
*/

typedef struct			s_session
{
	t_uchar	map[MEM_SIZE];
	int		spot_map[MEM_SIZE];
	int		cycle;
	int		period_lives;
	int		cycle_to_die;
	int		last_ctd;
	t_champ	*last_alive;
	t_carry	*carries;
	int		carry_num;
	int		total_champs;
	t_arg	*arg;
}						t_session;

/*
**	operation receives game (session), carries (carries), head of champs (champ)
*/

typedef bool	(*t_operation)(t_session *g, t_carry *ca, t_champ *h);

typedef struct			s_op
{
	char	name[PROG_NAME_LENGTH];
	int		nb_params;
	int		params_type[3];
	int		id;
	int		cycles;
	char	description[50];
	int		codage;
	int		label_size;
	bool	ind_idx;
}						t_op;

extern const t_op		g_optab[18];

#endif
