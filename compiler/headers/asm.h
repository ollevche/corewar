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
**	messages:
*/

# define NOT_COMPILED_ERR "File not compiled:"
# define READ_ERR "Can't read source file"
# define ENDLINE_ERR "Syntax error - unexpected end of input"
# define ENDLINE_HINT "(Perhaps you forgot to end with a newline ?)"
# define LEX_ERR "Lexical error at"
# define SYN_ERR "Syntax error at token [TOKEN]"
# define NSTR "INSTRUCTION"

# define SAFE_RET(I, R) { free_items(I); return (R); }
# define IF_RET(X, R) if (X) return (R);

# define ERR_TYPE	-1
# define LABEL_T	17 // label
# define COMM_T		18 // comment command
# define COMM_ML_T	19 // multiline comment command
# define NAME_T		20 // name command
# define NAME_ML_T	21 // multiline name command
# define STR_T		22 // line with already opened quote, contains closing quote
# define STR_ML_T	23 // line with already opened quote, doesn't contain any quotes
# define EMP_T		24

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
**	syntactically_valid.c
*/

int						syntactically_valid(char *line, int line_num);

/*
**	util.c
*/

int						skip_wspaces(char *line);
int						count_nwspaces(char *line);

/*
**	struct_funcs.c
*/

t_item					*new_item(char *line, int line_num, int type);
t_item					*add_item(t_item **head, char *ln, int nm, int tp);
void					free_items(t_item **head);

#endif
