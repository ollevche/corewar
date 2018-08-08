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

void	execute_carryes(t_session *game, t_champ *champs);
void	update_position(t_session *game, t_carry *carry, int val);

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
void    free_carryes(t_carry *carrys);

/*
**  operations:
*/

bool	live(t_session *game, t_carry *carry, t_champ *head);

#endif
