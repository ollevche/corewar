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
# include <unistd.h>
# include <sys/types.h>

/*
**	error messages:
*/

# define NOT_COMPILED_ERR "File not compiled:"
# define READ_ERR "Can't read source file"
# define ENDLINE_ERR "Syntax error - unexpected end of input"
# define ENDLINE_HINT "(Perhaps you forgot to end with a newline ?)"

# define SAFE_RET(I, R) { free_items(I); return (R); }
# define IF_RET(X, R) if ((X)) return (R);

# define NAME_T		19
# define COMMENT_T	18
# define LABEL_T	17

typedef unsigned char	t_uchar;

typedef struct			s_item
{
	int				type; // name (19) / comment (18) / label (17) / command (1 - 16)
	char			*line; // read line from a file
	int				line_num; // line id
	t_uchar			*bytecode; // bytecode representation of line
	int				bytecode_len; // number of bytes in bytecode
	bool			label_required; // is label used in line
	struct s_item	*next;
}						t_item;

/*
**	compile.c
*/

bool					compile(char *filename);

/*
**	read_sfile.c
*/

t_item					*read_sfile(char *filename);

/*
**	struct_funcs.c
*/

t_item					*new_item(char *line, int line_num);
t_item					*add_item(t_item **head, char *line, int line_num);
void					free_items(t_item **head);

#endif
