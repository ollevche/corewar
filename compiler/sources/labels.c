#include "asm.h"

bool	label_real(t_item *items, char *label_name)
{
	t_item *item;

	item = items;
	while (item)
	{
		if (item->type == LABEL_T && !ft_strequ(label_name, item->line))
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

	item = head;
	ret = true;
	while (item)
	{
		i = -1;
		while (++i < 3)
			if (ATYP(i) == T_LAB_DIR || ATYP(i) == T_LAB_IND)
				if (!label_real(items, item->it_arr[i + 1]))
					return (false);
		item = item->next;
	}
	return (true);
}