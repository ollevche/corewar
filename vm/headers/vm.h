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
# include "vm_funcs.h"
# include "stdbool.h"

# define RET_CHECK(X, R) if (!X) return (R);
# define EXIT_M(M) ft_printf("%s\n", M); free(M); exit(EXIT_FAILURE);
# define EX_CHECK(X, M) if (!X) {EXIT_M(M)}

typedef unsigned char	t_uchar;

typedef struct			s_carry
{
	t_uchar	regs[REG_SIZE];
	t_uchar	pc;
	bool	last_op;
}						t_carry;

/*
**	buff stores all of the champion file
**	name/comment/code is just a pointers to buff's parts
*/

typedef struct			s_champ
{
	t_carry			**carrys;
	int				id;
	t_uchar			*buff;
	t_uchar			*name;
	t_uchar			*comment;
	t_uchar			*code;
	bool			alive;
	struct s_champ	*next;
}						t_champ;

#endif
