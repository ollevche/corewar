/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblokha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 16:44:17 by vblokha           #+#    #+#             */
/*   Updated: 2018/09/26 16:44:19 by vblokha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	show_err(char *err_type, int line_num, int ind, char *str)
{
	ft_printf("%s [%03d:%03d]\n", err_type, line_num, ind + 1);
	if (str[0] != '\0')
		free(str);
	return (1);
}
