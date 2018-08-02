/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:29:16 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/02 13:29:17 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libftprintf.h"
# include "op.h"
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

# define ENDLINE_ERR "Syntax error - unexpected end of input"
# define ENDLINE_HINT "(Perhaps you forgot to end with a newline ?)"

typedef unsigned char	t_uchar;

typedef struct			s_item
{
	int				type;
	char			*line;
	int				line_num;
	t_uchar			*bytecode;
	struct s_item	*next;
}						t_item;

/*
**	compile.c
*/

bool					compile(char *filename);

/*
**	struct_funcs.c
*/

t_item					*new_item(char *line, int line_num);
t_item					*add_item(t_item **head, char *line, int line_num);
void					free_items(t_item **head);

#endif
