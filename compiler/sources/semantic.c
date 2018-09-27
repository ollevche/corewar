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

#define IT_ARR item->it_arr

int		is_command(char *line)
{
	int i;

	i = 0;
	while (i <= 16)
	{
		if (!ft_strequ(line, g_optab[i].name))
			return (g_optab[i].id);
		i++;
	}
	if (ft_strchr(line, LABEL_CHAR))
		return (LABEL_T);
	return (0);
}

int		analyze_arg(t_item *item, char *l, int i, bool validate)
{
	if (*l == DIRECT_CHAR)
	{
		if (validate)
		{
			if (!(OPT.params_type[i - 1] & T_DIR))
				return (false);
			if (*(l + 1) == LABEL_CHAR)
				return (T_LAB_DIR);
		}
		return (T_DIR);
	}
	if (*l == LABEL_CHAR)
	{
		if (validate)
		{
			if (!(OPT.params_type[i - 1] & T_IND))
				return (false);
			return (T_LAB_IND);
		}
		return (T_IND);
	}
	return (false);
}

int		get_arg_type(t_item *item, char *l, int i, bool validate)
{
	int	ret;

	ret = 0;
	IF_RET((validate && l && i > OPT.nb_params), 0);
	if (*l == REG_CHAR)
		ret = T_REG;
	else if (ft_isdigit(*l) || *l == '-')
		ret = T_IND;
	if (ret != 0)
	{
		if (validate)
			if (!(ret & OPT.params_type[i - 1]))
				return (false);
		return (ret);
	}
	return (analyze_arg(item, l, i, validate));
}

bool	validate_line(t_item *item)
{
	char	*trimmed;
	int		i;

	IF_RET(!(trimmed = ft_strtrim(item->line)), false);
	IF_RET(!(IT_ARR = split_line(trimmed)), false);
	free(trimmed);
	i = 1;
	if (!(item->type = is_command(IT_ARR[0])))
		return (print_err_msg(item, IT_ARR, i, -1));
	if (item->type == LABEL_T)
	{
		IT_ARR[0][ft_strlen(IT_ARR[0]) - 1] = '\0';
		IF_RET(!*IT_ARR[0], print_err_msg(item, IT_ARR, i, -5));
		return (true);
	}
	IF_RET(!IT_ARR[OPT.nb_params], print_err_msg(item, IT_ARR, i, -2));
	while (i <= OPT.nb_params + 1)
	{
		if (!IT_ARR[i] && i > OPT.nb_params)
			return (true);
		if (!(ATYP(i - 1) = get_arg_type(item, IT_ARR[i], i, true)))
			return (print_err_msg(item, IT_ARR, i, -3));
		i++;
	}
	return (true);
}

bool	semantically_valid(t_item *items)
{
	t_item	*item;

	item = items;
	while (item && item->type != 0)
		item = item->next;
	while (item)
	{
		if (!validate_line(item))
			return (false);
		fill_values(item);
		item = item->next;
	}
	item = items;
	if (!check_labels_existance(items))
		return (false);
	return (true);
}
