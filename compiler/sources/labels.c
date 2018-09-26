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

t_item	*find_label(t_item *items, char *label_name)
{
	t_item	*item;
	char	*actual_name;

	item = items;
	actual_name = label_name + (*label_name == '%' ? 2 : 1);
	while (item)
	{
		if (item->type == LABEL_T && !ft_strequ(actual_name, item->it_arr[0]))
			return (item);
		item = item->next;
	}
	return (NULL);
}

bool	check_labels_existance(t_item *items)
{
	t_item	*item;
	int		i;

	item = items;
	while (item)
	{
		i = -1;
		while (++i < 3)
			if (ATYP(i) == T_LAB_DIR || ATYP(i) == T_LAB_IND)
				if (!find_label(items, item->it_arr[i + 1]))
					return (print_err_msg(item, item->it_arr, i + 1, -4));
		item = item->next;
	}
	return (true);
}

void	fill_label_values(t_item *items)
{
	t_item	*item;
	t_item	*t;
	int		i;

	item = items;
	while (item)
	{
		i = -1;
		while (++i < 3)
			if (ATYP(i) == T_LAB_DIR || ATYP(i) == T_LAB_IND)
			{
				t = find_label(items, item->it_arr[i + 1]);
				AVAL(i) = t->starts_at - item->starts_at;
			}
		item = item->next;
	}
}

int		save_label(char *line, int line_num, t_item *head)
{
	int		i;

	i = skip_wspaces(line);
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (line[i] != LABEL_CHAR)
		return (0);
	add_item(&head, ft_strndup(line, i + 1), line_num, DEF_T);
	return (i + 1);
}
