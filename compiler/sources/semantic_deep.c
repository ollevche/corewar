/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_deep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:22:14 by dpozinen          #+#    #+#             */
/*   Updated: 2018/09/20 14:22:14 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fill_values(t_item *item)
{
	int i;

	i = 0;
	while (i < OPT.nb_params)
	{
		if (ATYP(i) == T_REG || ATYP(i) == T_DIR)
			AVAL(i) = ft_atoi(item->it_arr[i + 1] + 1);
		else if (ATYP(i) == T_IND)
			AVAL(i) = ft_atoi(item->it_arr[i + 1]);
		i++;
	}
}

bool	print_err_msg(t_item *item, char **it_arr, int i, int err_num)
{
	char	*arg_types[4];
	int		type;

	if (err_num == -1)
		ft_printf("Invalid instruction at token [TOKEN][%03d:001] \
INSTRUCTION \"%s\"\n", item->line_num, it_arr[0]);
	else if (err_num == -2)
		ft_printf("Invalid parameter count for instruction %s\n", it_arr[0]);
	else if (err_num == -3)
	{
		type = get_arg_type(item, it_arr[i], i, false);
		arg_types[0] = "register";
		arg_types[1] = "direct";
		arg_types[3] = "indirect";
		ft_printf("Invalid parameter %d type %s for instruction %s \
at line %d\n",
						i - 1, arg_types[type - 1], it_arr[0], item->line_num);
	}
	else if (err_num == -4)
		ft_printf("No such label %s at line %d\n",
		it_arr[i] + (*(it_arr[i]) == '%' ? 2 : 1), item->line_num);
	else if (err_num == -5)
		ft_printf("EMPTY LABEL\n");
	return (false);
}

char	*extract_command(char *trimmed, int *i)
{
	char	*line;
	char	*split_char;

	line = cut_word(trimmed);
	split_char = ft_strchr(line, DIRECT_CHAR);
	if (!split_char)
		split_char = ft_strchr(line, '-');
	if (split_char)
		*split_char = '\0';
	*i = ft_strlen(line);
	return (line);
}

char	**split_line(char *trimmed)
{
	char	**it_arr;
	int		i;
	char	*l;
	int		j;

	IF_RET(!(it_arr = (char**)ft_memalloc(sizeof(char*) * (4 + 1 + 1))), 0);
	i = 0;
	it_arr[0] = extract_command(trimmed, &i);
	l = trimmed;
	l += i;
	i = 1;
	while (i < 5 && *l)
	{
		j = 0;
		while (l[j] && l[j] != SEPARATOR_CHAR)
			j++;
		IF_RET(!(it_arr[i] = ft_strtrim_free(ft_strndup(l, j))), 0);
		l += j + 1;
		if (!*(l - 1))
			break ;
		l += skip_wspaces(l);
		i++;
	}
	return (it_arr);
}
