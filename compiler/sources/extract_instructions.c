/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:18:38 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/06 16:18:38 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	extract_instructions(int fd, t_item *head)
{
	char	*line;
	t_item	*new_item;
	int		line_num;

	//head = NULL;
	line_num = 3;
	//last_read = DEF_T;
	while ((line = safe_gnl(fd)))
	{
		new_item = add_item(&head, line, line_num, 0);
		//МОЯ ФУНКЦІЯ ПО ЗАПОВНЕННЮ СТАТИЧНОГО МАСИВУ ПОЇНТЕРІВ
			//new_item[0]
			//new_item[1]
			//new_item[2]
			//new_item[3]
			//new_item[4] = NULL;

		//ТВОЯ ПЕРЕВІРКА
		line_num++;
	}
}