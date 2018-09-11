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

int	static	error(int error, int line_num, int column, char *str)
{
	if (error == 1)
		return (ft_printf("Syntax error at token [TOKEN][%.3d:%.3d] SEPARATOR \",\"\n", line_num, column));
	if (error == 2)
		return (ft_printf("Syntax error at token [TOKEN][%.3d:%.3d] INDIRECT \"%s\"\n", line_num, column, str));
	if (error == 3)
		return (ft_printf("Syntax error at token [TOKEN][%.3d:%.3d] ENDLINE\n", line_num, column));

	return (0);
}

// int			check_arg(char *arg)
// {

// }

int			check_arguments(int index, t_item *item, char *start)
{
	char *arg;


	while(index && index > 1)
	{
		arg = item->colums[index] + skip_wspaces(item->colums[index] + 1) + 1;
		if (*arg == '\0')
			return (error(3, item->line_num, arg + 1 - start, NULL));
		while(*arg != ' ' && *arg)
			arg++;
		arg += skip_wspaces(arg);
		//if (*arg != '\0')
		//	return (error(2, item->line_num, arg + 1 - start, arg));
		index--;
	}

	return (0);
}

int static	get_colums(char *line, t_item *item)
{
	int		index;
	char	*start;
	char	comma;



	comma = 0;
	start = line;
	item->colums = (char**)ft_memalloc(sizeof(char *) * 5);
	index = 0;



	while(*line && index < 4)
	{
		if (index < 2)
		{
			if (*line == ',')
				return (error(1, item->line_num, line - start, NULL));
			if(*line != ' ')
			{
				item->colums[index++] = line;
				while(*line != ' ' && *line != '\0' && *line != ',')
					line++;
				continue ;
			}			
		}
		else
			if (*line == ',')
				item->colums[index++] = line;
		line++;
	}

	if (check_arguments(--index, item, start))
		return (3);
	


// if (*(item->colums[index] + skip_wspaces(item->colums[index] + 1) + 1) == '\0')
// 	exit(1);

ft_printf("%s<<<<<\n", item->colums[index]);
// ft_printf("\nindex: %d\n", skip_wspaces(item->colums[index] + 1));

	return (0);

}

void	extract_instructions(int fd, t_item *head)
{
	char	*line;
	t_item	*new_item;
	int		line_num;

	line_num = 3;
	while ((line = safe_gnl(fd)))
	{

		if (ft_strlen(line))
		{
			new_item = add_item(&head, line, line_num, 0);
			if (get_colums(line, new_item))
				exit(1);
		}
		line_num++;
	}
}