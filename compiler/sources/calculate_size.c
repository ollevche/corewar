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

static bool	check_length(t_item *item)
{
	int		size;
	bool	is_name;

	is_name = item->type == NAME_T;
	if (!is_name && item->type != COMM_T)
		return (true);
	size = ft_strlen(item->line);
	if (size >= (is_name ? PROG_NAME_LENGTH : COMMENT_LENGTH))
	{
		ft_printf("%s %d\n", (is_name ? TOLO_NAME : TOLO_COMMENT), size);
		return (false);
	}
	return (true);
}

bool		calculate_size(t_item *item)
{
	int		total_size;
	int		instructions;

	total_size = 0;
	instructions = 0;
	while (item)
	{
		if (item->type > 0 && item->type < 18)
			instructions++;
		SIZE = get_size(item);
		POS = total_size;
		total_size += SIZE;
		if (TYPE > 0 && TYPE < 17)
			g_codesize += SIZE;
		if (!check_length(item))
			return (false);
		item = item->next;
	}
	if (!instructions)
		ft_printf("%s\n", NO_INSTRUCTIONS);
	return (instructions > 0);
}
