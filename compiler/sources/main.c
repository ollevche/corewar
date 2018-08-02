/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:34:10 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/02 13:34:10 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	notes:
**		permits non .s files
**		displays usage if no files provided
**		doesn't permit no code
**		doesn't permit no name or no comment
**		last line has to be empty ("\n")
**		permits "" as name or comment
**		checks a name and a comment by size
**		permits separating words by space and tab (no matter len, 0 including)
**		rule: one item per line
**		empty line is a correct one
**		doesn't check for a code size (10k lines of code is ok)
**
**	bonus:
**		multiple files in one time
*/

int		main(int argc, char **args)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!compile(args[i]))
			ft_printf("File not compiled: %s\n", args[i]);
		i++;
	}
	return (0);
}
