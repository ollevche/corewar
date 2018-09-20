/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_semantic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:22:14 by dpozinen          #+#    #+#             */
/*   Updated: 2018/09/20 14:22:14 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

# define ATYP(i)	item->args[0][i]
# define AVAL(i)	item->args[1][i]
# define OPT		g_optab[item->type]

bool	fill_values(t_item *item, char **it_arr)
{
	int i;

	i = 0;
	while (i < OPT.nb_params)
	{
		if (ATYP(i) == T_REG || ATYP(i) == T_DIR)
			AVAL(i) = ft_atoi(((it_arr[i + 1]) + 1));
		else if (ATYP(i) == T_IND)
			AVAL(i) = ft_atoi(it_arr[i + 1]);
		i++;
	}
	return (1);
}

bool	print_err_msg(t_item *item, char **it_arr, int i, int err_num)
{
	char	*arg_types[4];
	int		type;

    if (err_num == -1)
        printf("Invalid instruction at token [TOKEN][%03d:001] INSTRUCTION \"%s\"", item->line_num, it_arr[0]);
	else if (err_num == -2)
		printf("Invalid parameter count for instruction %s\n", it_arr[0]);
    else
    {
        type = get_arg_type(item, it_arr[i], i, false);
        arg_types[0] = "register";
        arg_types[1] = "direct";
        arg_types[2] = "empty";
        arg_types[3] = "indirect";
        printf("Invalid parameter %d type %s for instruction %s\n", i - 1, arg_types[type - 1], it_arr[0]);
    }
	return (0);
}

char	**split_line(char *trimmed)
{
	char	**it_arr;
	int		i;
	char	*l;
	int		j;

	if (!(it_arr = (char**)ft_memalloc(sizeof(char*) * (4 + 1 + 1))))
		return (0);
	it_arr[0] = cut_word(trimmed);
	l = trimmed;
	l += count_nwspaces(trimmed) + 1;
	i = 1;
	while (i < 5 && *l)
	{
		j = 0;
		while (l[j] && l[j] != SEPARATOR_CHAR)
			j++;
		it_arr[i] = ft_strndup(l, j);
		l += j + 1;
		if (!*(l - 1))
			break ;
		l += skip_wspaces(l);
		i++;
	}
	return (it_arr);
}