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
	IF_RET((l == NULL && i <= OPT.nb_params), -2);
	*l == REG_CHAR ? ret = T_REG : 0;
	ft_isdigit(*l) ? ret = T_IND : 0;
	if (*l == DIRECT_CHAR)
	{
		if (validate && (OPT.params_type[i - 1] & T_DIR))
			ret = T_LAB_DIR;
		else
			ret = T_DIR;
	}
	else if (*l == LABEL_CHAR)
	{
		if (validate && (OPT.params_type[i - 1] & T_IND))
			ret = T_LAB_IND;
		else
			ret = T_IND;
	}
	if (validate && ret != T_LAB_DIR && ret != T_LAB_IND)
		ret = ret & (OPT.params_type[i - 1]);
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
		fill_values(item, it_arr);
		for (int i = 0; i < 3; i++) //
			printf("%d\n", AVAL(i)); //
		printf("-------------------------\n"); //

		item = item->next;
	}
	return (true);
}