/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 15:12:53 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/26 15:12:53 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define OP_CODE_SIZE	1

#define SIZE			item->size
#define CODE			item->bytecode
#define TYPE			item->type
#define ARG_TYPES		item->args[0]
#define ARG_VALUES		item->args[1]
#define POS				item->starts_at
#define LINE			item->line

static int	get_size(t_item *item)
{
	int	size;
	int	i;

	if (TYPE == NAME_T)
		return (PROG_NAME_LENGTH);
	if (TYPE == COMM_T)
		return (COMMENT_LENGTH);
	if (TYPE < 1 || TYPE > 16)
		return (0);
	size = OP_CODE_SIZE;
	size += g_optab[TYPE].codage;
	i = 0;
	while (i < 3 && ARG_TYPES[i])
	{
		if (ARG_TYPES[i] == T_REG)
			size += 1;
		else if (ARG_TYPES[i] == T_IND || ARG_TYPES[i] == T_LAB_IND)
			size += 2;
		else if (ARG_TYPES[i] == T_DIR || ARG_TYPES[i] == T_LAB_DIR)
			size += 2 + 2 * (1 - g_optab[TYPE].label_size);
		i++;
	}
	return (size);
}

void		calculate_size(t_item *item)
{
	int		total_size;

	total_size = 0;
	while (item)
	{
		SIZE = get_size(item);
		POS = total_size;
		total_size += SIZE;
		if (TYPE > 0 && TYPE < 17)
			g_codesize += SIZE;
		item = item->next;
	}
}
