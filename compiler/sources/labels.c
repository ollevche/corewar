/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:59:25 by dpozinen          #+#    #+#             */
/*   Updated: 2018/09/21 10:59:26 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	label_real(t_item *items, char *label_name)
{
	t_item	*item;
	char	*actual_name;

	item = items;
	actual_name = label_name + (*label_name == '%' ? 2 : 1);
	while (item)
	{
		if (item->type == LABEL_T && !ft_strequ(actual_name, item->line))
			return (true);
		item = item->next;
	}
	return (false);
}

bool	check_labels_existance(t_item *items)
{
	t_item	*item;
	int		i;
	bool	ret;

	item = items;
	ret = true;
	while (item)
	{
		if (item->type == LABEL_T)
			item->starts_at = item->next->line_num;
		i = -1;
		while (++i < 3)
			if (ATYP(i) == T_LAB_DIR || ATYP(i) == T_LAB_IND)
				if (!label_real(items, item->it_arr[i + 1]))
					return (print_err_msg(item, item->it_arr, i + 1, -4));
		item = item->next;
	}
	return (true);
}
