/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:01:41 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/19 17:01:44 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define OP_CODE_SIZE	1

#define SIZE			item->size
#define CODE			item->bytecode
#define TYPE			item->type
#define ARG_TYPES		item->args[0]
#define ARG_VALUES		item->args[1]

static int	get_size(t_item *item)
{
	int	size;
	int	i;

	size = OP_CODE_SIZE;
	size += g_optab[TYPE].codage;
	i = 0;
	while (i < 3 || ARG_TYPES[i])
	{
		if (ARG_TYPES[i] == REG_CODE)
			size += 1;
		else if (ARG_TYPES[i] == IND_CODE)
			size += 2;
		else if (ARG_TYPES[i] == DIR_CODE)
			size += 2 + 2 * g_optab[TYPE].label_size;
		i++;
	}
	return (size);
}

static void	set_codage(t_item *item)
{
	t_uchar	codage;
	t_uchar	type;
	int		i;

	if (!g_optab[TYPE].codage)
		return ;
	codage = 0;
	i = 0;
	while (i < 3 || ARG_TYPES[i])
	{
		type = ARG_TYPES[i];
		codage |= type << (6 - i * 2); // check it
		i++;
	}
	CODE[1] = codage;
}

static void	set_args(t_item *item)
{
	int	pos;

	pos = OP_CODE_SIZE + g_optab[TYPE].codage;
}

bool		to_bytecode(t_item *head)
{
	t_item	*item;

	item = head;
	while (item)
	{
		if (TYPE > 0 && TYPE < 17)
		{
			SIZE = get_size(item);
			CODE = (t_uchar*)malloc(sizeof(t_uchar) * SIZE);
			IF_RET(!CODE, false);
			CODE[0] = TYPE; // check conversion
			set_codage(item);
			set_args(item);
		}
		item = item->next;
	}
	return (true);
}
