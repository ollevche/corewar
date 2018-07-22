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
**  read_input.c
*/

t_champ	*read_input(int argc, char **args);

/*
**  validate_champ.c
*/

bool	validate_champ(char *arg, t_uchar **buffer, char **err_mes);

/*
**  play_the_game.c
*/

bool	play_the_game(t_champ *champs);


#endif
