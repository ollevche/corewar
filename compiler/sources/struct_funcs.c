/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:50:23 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/02 16:50:24 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_item	*new_item(char *line, int line_num, int type)
{
	t_item	*item;

	item = (t_item*)ft_memalloc(sizeof(t_item));
	if (!item)
		return (NULL);
	item->type = type;
	item->line = line;
	item->line_num = line_num;
	item->bytecode = NULL;
	item->starts_at = -1;
	item->next = NULL;
	return (item);
}

t_item	*add_item(t_item **head, char *line, int line_num, int type)
{
	t_item	*item;
	t_item	*iter;

	item = new_item(line, line_num, type);
	if (!item)
		return (NULL);
	if (*head)
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = item;
	}
	else
		*head = item;
	return (item);
}

void	free_items(t_item **head)
{
	(void)head;
	// TODO: this
}

bool		has_item(int target_type, t_item *head)
{
	if (head == NULL)
		return (false);
	while (head)
	{
		if (head->type == target_type)
			return (true);
		head = head->next;
	}
	return (false);
}

t_item		*get_last(t_item *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}
