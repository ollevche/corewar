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
# define ENDLINE_ERR "Unexpected end of input"
# define ENDLINE_HINT "(Perhaps you forgot to end with a newline ?)"
# define NOHDR_ERR "Expected header item ('.name' or '.comment') after line:"
# define HDR_DOUBL "Repeatable header commands are not acceptable"
# define QUOTE_ERR "Syntax error: expected quotation mark at"
# define UNDEF_ERR "Syntax error: undefined token at"
# define NO_ARG_ERR "Syntax error: expected argument after"
# define INVALID_ARG "Syntax error: invalid argument at"
# define INVALID_COMM "Syntax error: invalid character at"
# define NO_SEPARATOR "Syntax error: expected separator after"
# define NO_INSTRUCTIONS "Error: File has no instructions"
# define TOLO_NAME "Champion name too long: max length 128, champ length"
# define TOLO_COMMENT "Champion comment too long max length 2048, champ length"

# define SAFE_RET(I, R) { free_items(I); return (R); }
# define IF_RET(X, R) if (X) return (R);
# define IS_WSPACE(C) (C == '\t' || C == ' ')

# define ATYP(i)	item->args[0][i]
# define AVAL(i)	item->args[1][i]
# define OPT		g_optab[item->type]

# define ERR_T		-1
# define DEF_T		0
# define LABEL_T	17
# define COMM_T		18
# define NAME_T		19

typedef unsigned char	t_uchar;

/*
**	int				type; // type of the line (command / label / comment / name)
**	char			*line; // read line from a file
**	int				line_num; // line id
**	t_uchar			*bytecode; // bytecode representation of line
**	int				size;
**	int				starts_at; // index of first byte in the whole code
**	int				args[2][3]; // argument types[0] and values[1]
**	char			**it_arr; // has no init value
*/

typedef struct			s_item
{
	int				type;
	char			*line;
	int				line_num;
	t_uchar			*bytecode;
	int				size;
	int				starts_at;
	int				args[2][3];
	char			**it_arr;
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
extern int				g_codesize;

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
**	to_bytecode.c
*/

bool					to_bytecode(t_item *head);

/*
**	calculate_size.c
*/

bool					calculate_size(t_item *item);

/*
**	semantic.c
*/

bool					semantically_valid(t_item *item_h);
int						get_arg_type(t_item *item, char *l, int i,
											bool validate);

/*
**	deep_semantic.c
*/

bool					print_err_msg(t_item *item, char **it_arr, int i,
											int err_num);
void					fill_values(t_item *item);
void					fill_label_values(t_item *items);
char					**split_line(char *trimmed);

/*
**	labels.c
*/

bool					check_labels_existance(t_item *items);
int						save_label(char *line, int line_num, t_item *head);

/*
**	writing.c
*/

bool					write_corfile(char *filename, t_item *items);

/*
**	struct_funcs.c
*/

t_item					*new_item(char *line, int line_num, int type);
t_item					*add_item(t_item **head, char *ln, int nm, int tp);
t_item					*get_last(t_item *head);
t_item					*get_item_by_type(int target_type, t_item *head);
void					free_items(t_item **head);

/*
**	util.c
*/

char					*cut_word(char *line);
int						skip_wspaces(char *line);
int						count_nwspaces(char *line);
bool					is_empty(char *line);
void					trim_comments(char *line);

/*
**	header_err.c
*/

int						show_err(char *err_type, int line_num,
								int ind, char **str);

#endif
