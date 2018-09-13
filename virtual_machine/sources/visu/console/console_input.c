/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:31:40 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/03 20:31:40 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_msg	*create_console_input(t_vdata *vdata)
{
	t_msg *input_line;

	input_line = (t_msg*)ft_memalloc(sizeof(t_msg));
	ft_strcpy(input_line->prefix, "Corewar:");
	input_line->total_lines = 1;
	input_line->left_lines = 1;
	ft_bzero(vdata->console.input_line, CONSOLE_INPUT_LEN);
	input_line->text = vdata->console.input_line;
	input_line->text[0] = ' ';
	return (input_line);
}
