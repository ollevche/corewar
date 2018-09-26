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
**	main.c ▽
*/

void	terminate();

/*
**  display_and_log.c ▽
*/

void	display_contestants(t_champ *champs, t_arg *arg);
void	display_winner(t_champ *winner, t_arg *arg);
void	display_usage();
void	log_cycles(t_session *game, t_arg *arg, bool game_over);
void	log_operation(t_session *game, int new_pc, int old_pc);

/*
**	read_input.c ▽
*/

t_champ	*read_input(int argc, char **args, t_arg *arg);

/*
**	read_champ.c ▽
*/

t_champ	*read_champ(t_champ **champs, int fd, char *filename);

/*
**  prepare.c ▽
*/

bool	prepare(t_champ *champs, t_session **game, t_arg *arg);

/*
**	play_the_game.c ▽
*/

t_champ	*play_the_game(t_champ *champs, t_arg *arg);

/*
**  execution.c ▽
*/

void	execute_carries(t_session *game, t_champ *champs);

/*
**  util.c
*/

void	update_position(t_carry *carry, int val);
void	update_opcode(t_session *game, t_carry *carry);
int		move_pc(int pc, int val);
int		count_champs(t_champ *champs);

/*
**	struct_funcs.c ▽
*/

t_champ	*new_champ(t_champ **champs);
t_carry *new_carry(t_carry **all_carries, int first_reg);
t_champ	*get_champ_by_id(t_champ *head, int id);
void	del_carry(t_carry **head, t_carry *prev, t_carry *target);
t_champ	*get_last_champ(t_champ *head);

/*
**	free_funcs.c ▽
*/

void	free_session(t_session **game);
void	free_champs(t_champ **champs);
void	free_carries(t_carry **carries);

/*
**  operations ▽
**  return values are not so random
*/

bool	live(t_session *game, t_carry *carry, t_champ *head);
bool	ld(t_session *game, t_carry *carry, t_champ *head);
bool	st(t_session *game, t_carry *carry, t_champ *head);
bool	add(t_session *game, t_carry *carry, t_champ *head);
bool	sub(t_session *game, t_carry *carry, t_champ *head);
bool	and(t_session *game, t_carry *carry, t_champ *head);
bool	or(t_session *game, t_carry *carry, t_champ *head);
bool	xor(t_session *game, t_carry *carry, t_champ *head);
bool	zjmp(t_session *game, t_carry *carry, t_champ *head);
bool	ldi(t_session *game, t_carry *carry, t_champ *head);
bool	sti(t_session *game, t_carry *carry, t_champ *head);
bool	op_fork(t_session *game, t_carry *carry, t_champ *head);
bool	lld(t_session *game, t_carry *carry, t_champ *head);
bool	lldi(t_session *game, t_carry *carry, t_champ *head);
bool	op_lfork(t_session *game, t_carry *carry, t_champ *head);
bool	aff(t_session *game, t_carry *carry, t_champ *head);
int		set_arg_types(int coding_byte, int *args, int size);

/*
**  base_ops.c ▽
*/

bool	base_fork(t_session *game, t_carry *carry, bool idx);

/*
**	op_tools.c ▽
*/

bool	set_arg_values(int args[2][4], int *lpc, t_session *game, int op_code);
int		get_value_by_arg(t_session *game, int arg, int lpc, int op_code);
bool	check_reg(int *value, t_carry *carry, int jmp);

/*
**	op_tools_more.c ▽
*/

bool	check_cbyte(int args[2][4], int op_code, int size);
void	write_to_map(t_session *game, int pos, int value, int champ_id);
t_uint	read_int(t_session *game, int lpc, int n_bytes, bool plus_one);

#endif
