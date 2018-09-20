#include "asm.h"

bool	check_label_existance(t_item *items)
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
				if (!label_real(items))
					return (0);
		item = item->next;
	}
}