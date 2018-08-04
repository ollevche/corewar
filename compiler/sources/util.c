/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 13:19:09 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/04 13:19:09 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	skip_wspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	return (i);
}

int	count_nwspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\t' && line[i] != ' ')
		i++;
	return (i);
}
