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
	if (ft_strchr(line, LABEL_CHAR))
		ret = LABEL_T;
	free(line);
	return (ret);
}

int		get_arg_type(t_item *item, char *l, int i, bool validate)
{
	int	ret;

	ret = 0;
	if (l == NULL && i <= OPT.nb_params)
		return (-2);
	if (*l == REG_CHAR)
		ret = T_REG;
	else if (*l == DIRECT_CHAR)
		ret = (*(l + 1) == LABEL_CHAR && validate) ? T_LAB : T_DIR;
	if (ft_isdigit(*l))
		ret = T_IND;
	if (*l == LABEL_CHAR)
		ret = validate ? T_LAB : T_IND;
	if (validate && ret != T_LAB)
		return (OPT.params_type[i - 1] & ret);
	return (ret);
}

bool	validate_line(t_item *item, char ***it_arr)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(item->line);
	*it_arr = split_line(trimmed);
	free(trimmed);

	// for (int i = 0; i < 5; i++) //
	// 	if ((*it_arr)[i]) //
	// 		printf("%s\n", (*it_arr)[i]); //
	// printf("\n"); //

	i = 1;
	if (!(item->type = is_command((*it_arr)[0])))
		return (print_err_msg(item, *it_arr, i, -1));
	while (i < OPT.nb_params + 1)
	{
		if ((ATYP(i - 1) = get_arg_type(item, (*it_arr)[i], i, true)) <= 0)
			return (print_err_msg(item, *it_arr, i, ATYP(i - 1)));
		i++;
	}
	return (true);
}

bool	semantically_valid(t_item *item_h)
{
	t_item	*item;
	char	**it_arr;

	item = item_h;
	while (item && item->type != 0)
		item = item->next;
	it_arr = 0;
	while (item)
	{
		if (!validate_line(item, &it_arr))
		{
			// free it_arr here
			// printf("semantic error\n"); //
			return (false);
		}

		for (int i = 0; i < 3; i++) //
			printf("%d\n", ATYP(i)); //
		printf("\n"); //
		if (!fill_values(item, it_arr))
			return (false);
		for (int i = 0; i < 3; i++) //
			printf("%d\n", AVAL(i)); //
		printf("-------------------------\n"); //

		item = item->next;
	}
	return (true);
}