/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:50:01 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/18 14:50:01 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_FUNCS_H
# define VM_FUNCS_H

# include "vm.h"

/*
** DEFINES FOR READABILITY ▽
*/

# define TYP1 args[0][0]
# define TYP2 args[0][1]
# define TYP3 args[0][2]
# define VAL1 args[1][0]
# define VAL2 args[1][1]
# define VAL3 args[1][2]

/*
**	main.c
*/

void	terminate();
void	display_usage(char *usage_txt);

/*
**	read_input.c
*/

t_champ	*read_input(int argc, char **args, t_arg *arg);


/*
**	read_champ.c
*/

t_champ	*read_champ(t_champ **champs, int fd, char *filename);

/*
**  prepare.c
*/

bool	prepare(t_champ *champs, t_session **game);

/*
**	play_the_game.c
*/

t_champ	*play_the_game(t_champ *champs, t_arg *arg);

/*
**  execution.c
*/

void	execute_carries(t_session *game, t_champ *champs);
void	update_position(t_session *game, t_carry *carry, int val);
int		move_pc(t_session *game, int pc, int val);

/*
**	struct_funcs.c
*/

t_champ	*new_champ(t_champ **champs);
bool	new_carry(t_carry **all_carrys, int first_reg);
void	del_carry(t_carry **carrys, t_carry *target);
t_champ	*get_champ_by_id(t_champ *head, int id);

/*
**	free_funcs.c
*/

void	free_session(t_session **game);
void	free_champs(t_champ **champs);
void    free_carries(t_carry *carrys);

/*
**  operations ▽
*/

bool	live(t_session *game, t_carry *carry, t_champ *head);
bool	ld(t_session *game, t_carry *carry, t_champ *head);
bool	add(t_session *game, t_carry *carry, t_champ *head);
bool	sub(t_session *game, t_carry *carry, t_champ *head);
bool	st(t_session *game, t_carry *carry, t_champ *head);

/*
**	op_tools.c ▽
*/

void	get_arg_types(int coding_byte, int *arg1, int *arg2, int *arg3);
int 	get_value_by_arg(t_session *game, int arg, int lpc, bool idx_mod);
int     get_pc_move(int arg);
int		*get_arg_values(int *arg_types, int *lpc, t_session *game, bool idx_m);
bool	check_reg(int *value, t_session *game, t_carry *carry, int lpc);

#endif
