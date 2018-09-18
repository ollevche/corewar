/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:07:47 by dpozinen          #+#    #+#             */
/*   Updated: 2018/09/18 15:07:47 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

# define FREE_RET(x, y) if (!(x)) { free(y); return (false); }

# define ATYP(i)	item->args[0][i]
# define AVAL(i)	item->args[1][i]
# define OPT		g_optab[item->type]

int		is_command(char *line)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < 16)
	{
		if (!ft_strequ(line, g_optab[i].name))
			ret = g_optab[i].id;
		i++;
	}
	if (ft_strchr(line, ':'))
		ret = LABEL_T;
	free(line);
	return (ret);
}

int		validate_arg(t_item *item, char *l, int i)
{
	if (l == NULL && i < OPT.nb_params)
		return (0);
	if (*l == 'r' && (OPT.params_type[i - 1] & 1))
		return (1);
	if (*l == '%' && (OPT.params_type[i - 1] & 2))
		return (2);
	if ((ft_isdigit(*l) || *l == ':') && (OPT.params_type[i - 1] & 4))
		return (4);
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
		while (l[j] && l[j] != ',')
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

bool	validate_line(t_item *item)
{
	char	*trimmed;
	int		i;
	char	**it_arr;

	trimmed = ft_strtrim(item->line);
	it_arr = split_line(trimmed);
	for (int i = 0; i < 5; i++)
		printf("%s\n", it_arr[i]);
	if (!(item->type = is_command(it_arr[0])))
		return (0); // LEAKS
	if (it_arr[OPT.nb_params + 1] != NULL)
		return (0); // LEAKS
	i = 1;
	while (i < OPT.nb_params + 1)
	{
		if (!(ATYP(i - 1) = validate_arg(item, it_arr[i], i)))
			return (0);
		i++;
	}
	return (true);
}

bool	semantically_valid(t_item *item_h)
{
	t_item *item;
	(void)item_h;
	// while (item && item->type != 0)
	// 	item = item->next;
	// while (item)
	// {
		item = new_item(ft_strdup("zjmp %:loop"), 3, 0);
		if (!validate_line(item))
			return (false);
		for (int i = 0; i < 3; i++)
			printf("%d\n", ATYP(i));
		// if (!save_args(item))
		// 	return (false);
		// item = item->next;
	// }
	return (true);
}