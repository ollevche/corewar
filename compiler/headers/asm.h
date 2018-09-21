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

# define ERROR_M "ERROR:"
# define NOT_COMPILED_ERR "File not compiled:"
# define READ_ERR "Can't read source file"
# define ENDLINE_ERR "Unexpected end of input"
# define ENDLINE_HINT "(Perhaps you forgot to end with a newline ?)"
# define NOHDR_ERR "Expected header item ('.name' or '.comment') after line:"
# define HDR_DOUBL "Repeatable header commands are not acceptable"
# define QUOTE_ERR "Expected quote at"
# define UNDEF_ERR "Undefined token at"
# define SYNTAX_ERR "Syntax error near"

# define SAFE_RET(I, R) { free_items(I); return (R); }
# define IF_RET(X, R) if (X) return (R);

# define ATYP(i)	item->args[0][i]
# define AVAL(i)	item->args[1][i]
# define OPT		g_optab[item->type]

# define ERR_T		-1 // error value of TYPES
# define DEF_T		0 // default value
# define LABEL_T	17 // label
# define COMM_T		18 // comment command
# define NAME_T		19 // name command // og 20

typedef unsigned char	t_uchar;

typedef struct			s_item
{
	int				type; // type of the line (command / label / comment / name)
	char			*line; // read line from a file
	int				line_num; // line id
	t_uchar			*bytecode; // bytecode representation of line
	int				size;
	int				starts_at; // index of first byte in the whole code
	int				args[2][3]; // argument types[0] and values[1] // has no init value
	char			**it_arr; // has no init value
	struct s_item	*next;
}						t_item;

typedef struct			s_op
{
	char	name[PROG_NAME_LENGTH];
	int		nb_params;
	int		params_type[3];
	int		id;
	int		cycles;
	char	description[50];
	int		codage;
	int		label_size;
	bool	ind_idx;
}						t_op;

extern const t_op		g_optab[18];

/*
**	compile.c
*/

bool					compile(char *filename);

/*
**	read_sfile.c
*/

t_item					*read_sfile(char *filename);

/*
**	extract_header.c
*/

t_item					*extract_header(int fd);

/*
**	extract_instructions.c
*/

bool					extract_instructions(int fd, t_item *head);

/*
**	util.c
*/

char					*cut_word(char *line);
int						skip_wspaces(char *line);
int						count_nwspaces(char *line);
bool					is_empty(char *line);
void					trim_comments(char *line);

/*
**	struct_funcs.c
*/

t_item					*new_item(char *line, int line_num, int type);
t_item					*add_item(t_item **head, char *ln, int nm, int tp);
void					free_items(t_item **head);
bool					has_item(int target_type, t_item *head);
t_item					*get_last(t_item *head);

/*
**	semantic.c
*/

bool					semantically_valid(t_item *item_h);
int						get_arg_type(t_item *item, char *l, int i, bool validate);

/*
**	deep_semantic.c
*/

bool					print_err_msg(t_item *item, char **it_arr, int i, int err_num);
void					fill_values(t_item *item, char **it_arr);
char					**split_line(char *trimmed);

/*
**	labels.c
*/

bool					check_labels_existance(t_item *items);

#endif
