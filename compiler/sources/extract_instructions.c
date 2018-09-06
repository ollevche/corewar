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

void static	get_colums(char *line, t_item *item)
{
	int		index;
	
	item->colums = (char**)ft_memalloc(sizeof(char *) * 5);
	index = 0;
	while(*line && index < 5)
	{
		if(*line != ' ')
		{
			item->colums[index] = line;
			index++;
			while(*line != ' ' && *line != '\0')
				line++;
		}
		line++;
	}

	//TEST PRINTING
	index = 0;
	while(index < 5)
	{	if (item->colums[index])
			ft_printf("colum: %s\n", item->colums[index]);
			index++;
	}

}

void	extract_instructions(int fd, t_item *head)
{
	char	*line;
	t_item	*new_item;
	int		line_num;

	line_num = 3;
	while ((line = safe_gnl(fd)))
	{
		new_item = add_item(&head, line, line_num, 0);
		get_colums(line, new_item);	//МОЯ ФУНКЦІЯ ПО ЗАПОВНЕННЮ СТАТИЧНОГО МАСИВУ ПОЇНТЕРІВ
			//new_item[0] = command name
			//new_item[1] = arg 1
			//new_item[2] = arg 2
			//new_item[3] = arg 3
			//new_item[4] = NULL;

		//ТВОЯ ПЕРЕВІРКА
		line_num++;
	}
}